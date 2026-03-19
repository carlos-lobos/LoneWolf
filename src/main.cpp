#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "Ast/AstNode.h"

class AstPrinter : public ASTNodeVisitor {
public:
    void print(ASTNode* node) {
        if (node) {
            node->accept(*this);
        }
    }

    void visitBinaryExpression(BinaryExpression& node) override {
        std::cout << "(binary ";
        std::cout << node.getOp() << " ";
        print(node.getLeft());
        std::cout << " ";
        print(node.getRight());
        std::cout << ")";
    }

    void visitUnaryExpression(UnaryExpression& node) override {
        std::cout << "(unary " << node.getOp() << " ";
        print(node.getOperand());
        std::cout << ")";
    }

    void visitLiteralExpression(LiteralExpression& node) override {
        std::cout << node.getValue();
    }

    void visitIdentifierExpression(IdentifierExpression& node) override {
        std::cout << node.getId();
    }

    void visitGroupedExpression(GroupedExpression& node) override {
        std::cout << "(group ";
        print(node.getInner());
        std::cout << ")";
    }

    void visitAssignmentStatement(AssignmentStatement& node) override {
        std::cout << "(assign ";
        print(node.getLhs());
        std::cout << " ";
        print(node.getRhs());
        std::cout << ")";
    }

    void visitExpressionStatement(ExpressionStatement& node) override {
        print(node.getExpr());
    }

    void visitIfStatement(IfStatement& node) override {
        std::cout << "(if ";
        print(node.getCondition());
        std::cout << " ";
        print(node.getThenBranch());
        if (node.getElseBranch()) {
            std::cout << " ";
            print(node.getElseBranch());
        }
        std::cout << ")";
    }

    void visitWhileStatement(WhileStatement& node) override {
        std::cout << "(while ";
        print(node.getCondition());
        std::cout << " ";
        print(node.getBody());
        std::cout << ")";
    }

    void visitReturnStatement(ReturnStatement& node) override {
        std::cout << "(return";
        if (node.getValue()) {
            std::cout << " ";
            print(node.getValue());
        }
        std::cout << ")";
    }

    void visitBlockStatement(BlockStatement& node) override {
        std::cout << "(block";
        for (const auto& stmt : node.getStatements()) {
            std::cout << " ";
            print(stmt);
        }
        std::cout << ")";
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "[USO] ./lonewolf <archivo>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir el archivo '" << argv[1] << "'" << std::endl;
        return 1;
    }

    std::vector<std::string> sourceLines;
    std::string lineText;

    while (std::getline(file, lineText)) {
        sourceLines.push_back(lineText);
    }

    file.clear();
    file.seekg(0);

    ErrorCollector errors;

    Lexer lexer(file, errors);

    Token token;
    do {
        token = lexer.getNextToken();

        std::cout << tokenTypeToString(token.type)
          << " : "
          << token.lexeme
          << std::endl;

    } while (token.type != TokenType::END_OF_FILE);

    file.clear();
    file.seekg(0);

    Lexer parserLexer(file, errors);
    Parser parser(parserLexer, errors);

    std::vector<Statement*> statements = parser.parse();

    if (!errors.hasErrors()) {
        std::cout << "\n=== AST ===" << std::endl;
        AstPrinter printer;
        for (auto* stmt : statements) {
            printer.print(stmt);
            std::cout << std::endl;
        }
    }

    for (auto* stmt : statements) {
        delete stmt;
    }

    if (errors.hasErrors()) {
        std::cout << "\nErrores encontrados:\n\n";

        for (const auto& err : errors.getErrors()) {

            std::cout << argv[1]
                    << ":" << err.line
                    << ":" << err.column
                    << " \033[31merror:\033[0m "
                    << err.message
                    << "\n\n";

            if (err.line > 0 && err.line <= sourceLines.size()) {

                const std::string& codeLine = sourceLines[err.line - 1];

                std::cout << codeLine << std::endl;

                for (int i = 1; i < err.column; i++)
                    std::cout << " ";

                std::cout << "^" << std::endl;
            }

            std::cout << std::endl;
        }
    }

    return 0;
}
