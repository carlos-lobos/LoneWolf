#pragma once

#include <vector>
#include <string>
#include "ErrorCollector.h"
#include "Ast/AstNode.h"
#include "semantic/SymbolTable.h"
#include "semantic/Type.h"

class SemanticAnalyzer : public ASTNodeVisitor {
public:
    explicit SemanticAnalyzer(ErrorCollector& errorCollector);

    void analyze(const std::vector<Statement*>& statements);

    void visitBinaryExpression(BinaryExpression& node) override;
    void visitUnaryExpression(UnaryExpression& node) override;
    void visitLiteralExpression(LiteralExpression& node) override;
    void visitIdentifierExpression(IdentifierExpression& node) override;
    void visitGroupedExpression(GroupedExpression& node) override;

    void visitAssignmentStatement(AssignmentStatement& node) override;
    void visitExpressionStatement(ExpressionStatement& node) override;
    void visitIfStatement(IfStatement& node) override;
    void visitWhileStatement(WhileStatement& node) override;
    void visitReturnStatement(ReturnStatement& node) override;
    void visitBlockStatement(BlockStatement& node) override;

private:
    ErrorCollector& errorCollector;
    SymbolTable symbolTable;
    Type* currentReturnType;

    Type* getExprType(ASTNode* node);
    void setExprType(ASTNode* node, Type* type);

    void addError(const std::string& message, int line, int column);
};
