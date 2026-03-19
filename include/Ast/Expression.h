#pragma once

#include <string>
#include "Ast/AstNode.h"

class BinaryExpression : public Expression {
public:
    BinaryExpression(Expression* left, const std::string& op, Expression* right, int line, int column)
        : Expression(line, column), left(left), op(op), right(right) {}

    ~BinaryExpression() {
        delete left;
        delete right;
    }

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitBinaryExpression(*this);
    }

    Expression* getLeft() const { return left; }
    const std::string& getOp() const { return op; }
    Expression* getRight() const { return right; }

private:
    Expression* left;
    std::string op;
    Expression* right;
};

class UnaryExpression : public Expression {
public:
    UnaryExpression(const std::string& op, Expression* operand, int line, int column)
        : Expression(line, column), op(op), operand(operand) {}

    ~UnaryExpression() {
        delete operand;
    }

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitUnaryExpression(*this);
    }

    const std::string& getOp() const { return op; }
    Expression* getOperand() const { return operand; }

private:
    std::string op;
    Expression* operand;
};

class LiteralExpression : public Expression {
public:
    LiteralExpression(const std::string& value, int line, int column)
        : Expression(line, column), value(value) {}

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitLiteralExpression(*this);
    }

    const std::string& getValue() const { return value; }

private:
    std::string value;
};

class IdentifierExpression : public Expression {
public:
    IdentifierExpression(const std::string& id, int line, int column)
        : Expression(line, column), id(id) {}

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitIdentifierExpression(*this);
    }

    const std::string& getId() const { return id; }

private:
    std::string id;
};

class GroupedExpression : public Expression {
public:
    GroupedExpression(Expression* inner, int line, int column)
        : Expression(line, column), inner(inner) {}

    ~GroupedExpression() {
        delete inner;
    }

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitGroupedExpression(*this);
    }

    Expression* getInner() const { return inner; }

private:
    Expression* inner;
};
