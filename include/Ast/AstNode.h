#pragma once

#include <string>
#include <vector>
#include <memory>
#include "semantic/Type.h"

class ASTNodeVisitor;

class ASTNode {
public:
    virtual ~ASTNode() = default;

    virtual void accept(ASTNodeVisitor& visitor) = 0;

    int getLine() const { return line; }
    int getColumn() const { return column; }

    Type* getType() const { return type.get(); }
    void setType(Type* t) { type.reset(t); }

protected:
    ASTNode(int line = 0, int column = 0) : line(line), column(column), type(nullptr) {}

    int line;
    int column;
    std::unique_ptr<Type> type;
};

class Statement : public ASTNode {
public:
    using ASTNode::ASTNode;
    virtual ~Statement() = default;
};

class Expression : public ASTNode {
public:
    using ASTNode::ASTNode;
    virtual ~Expression() = default;
};

class ASTNodeVisitor {
public:
    virtual ~ASTNodeVisitor() = default;

    virtual void visitBinaryExpression(class BinaryExpression& node) = 0;
    virtual void visitUnaryExpression(class UnaryExpression& node) = 0;
    virtual void visitLiteralExpression(class LiteralExpression& node) = 0;
    virtual void visitIdentifierExpression(class IdentifierExpression& node) = 0;
    virtual void visitGroupedExpression(class GroupedExpression& node) = 0;

    virtual void visitAssignmentStatement(class AssignmentStatement& node) = 0;
    virtual void visitExpressionStatement(class ExpressionStatement& node) = 0;
    virtual void visitIfStatement(class IfStatement& node) = 0;
    virtual void visitWhileStatement(class WhileStatement& node) = 0;
    virtual void visitReturnStatement(class ReturnStatement& node) = 0;
    virtual void visitBlockStatement(class BlockStatement& node) = 0;
};
