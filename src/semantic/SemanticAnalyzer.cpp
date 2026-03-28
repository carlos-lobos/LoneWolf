#include "semantic/SemanticAnalyzer.h"
#include <iostream>
#include "ErrorCollector.h"
#include "Ast/Expression.h"
#include "Ast/Statement.h"
#include "semantic/Symbol.h"

SemanticAnalyzer::SemanticAnalyzer(ErrorCollector& errorCollector)
    : errorCollector(errorCollector), currentReturnType(nullptr) {}

void SemanticAnalyzer::analyze(const std::vector<Statement*>& statements) {
    for (auto* stmt : statements) {
        stmt->accept(*this);
    }
}

void SemanticAnalyzer::addError(const std::string& message, int line, int column) {
    errorCollector.addError(message, line, column);
}

void SemanticAnalyzer::setExprType(ASTNode* node, Type* type) {
    node->setType(type);
}

void SemanticAnalyzer::visitBinaryExpression(BinaryExpression& node) {
    node.getLeft()->accept(*this);
    node.getRight()->accept(*this);
}

void SemanticAnalyzer::visitUnaryExpression(UnaryExpression& node) {
    node.getOperand()->accept(*this);
}

void SemanticAnalyzer::visitLiteralExpression(LiteralExpression& node) {
}

void SemanticAnalyzer::visitIdentifierExpression(IdentifierExpression& node) {
    const std::string& name = node.getId();
    Symbol* symbol = symbolTable.resolve(name);

    if (!symbol) {
        addError("Undefined variable: " + name, node.getLine(), node.getColumn());
        return;
    }
}

void SemanticAnalyzer::visitGroupedExpression(GroupedExpression& node) {
    node.getInner()->accept(*this);
}

void SemanticAnalyzer::visitAssignmentStatement(AssignmentStatement& node) {
    node.getRhs()->accept(*this);

    IdentifierExpression* lhs = dynamic_cast<IdentifierExpression*>(node.getLhs());
    if (!lhs) {
        addError("Invalid assignment target", node.getLine(), node.getColumn());
        return;
    }

    const std::string& name = lhs->getId();

    Symbol* existing = symbolTable.resolve(name);
    if (!existing) {
        VariableSymbol* var = new VariableSymbol(name, new UnknownType());
        symbolTable.define(var);
    }
}

void SemanticAnalyzer::visitExpressionStatement(ExpressionStatement& node) {
    node.getExpr()->accept(*this);
}

void SemanticAnalyzer::visitIfStatement(IfStatement& node) {
    node.getCondition()->accept(*this);

    symbolTable.enterScope();
    node.getThenBranch()->accept(*this);
    symbolTable.exitScope();

    if (node.getElseBranch()) {
        symbolTable.enterScope();
        node.getElseBranch()->accept(*this);
        symbolTable.exitScope();
    }
}

void SemanticAnalyzer::visitWhileStatement(WhileStatement& node) {
    node.getCondition()->accept(*this);

    symbolTable.enterScope();
    node.getBody()->accept(*this);
    symbolTable.exitScope();
}

void SemanticAnalyzer::visitReturnStatement(ReturnStatement& node) {
    if (node.getValue()) {
        node.getValue()->accept(*this);
    }
}

void SemanticAnalyzer::visitBlockStatement(BlockStatement& node) {
    for (auto* stmt : node.getStatements()) {
        stmt->accept(*this);
    }
}

Type* SemanticAnalyzer::getExprType(ASTNode* node) {
    if (dynamic_cast<BinaryExpression*>(node)) {
        return dynamic_cast<BinaryExpression*>(node)->getType();
    } else if (dynamic_cast<UnaryExpression*>(node)) {
        return dynamic_cast<UnaryExpression*>(node)->getType();
    } else if (dynamic_cast<LiteralExpression*>(node)) {
        return dynamic_cast<LiteralExpression*>(node)->getType();
    } else if (dynamic_cast<IdentifierExpression*>(node)) {
        return dynamic_cast<IdentifierExpression*>(node)->getType();
    } else if (dynamic_cast<GroupedExpression*>(node)) {
        return dynamic_cast<GroupedExpression*>(node)->getType();
    }
    return new UnknownType();
}
