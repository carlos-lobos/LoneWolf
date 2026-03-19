#pragma once

#include <string>
#include <vector>
#include "Ast/AstNode.h"
#include "Ast/Expression.h"

class IdentifierExpression;
class Expression;

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(IdentifierExpression* lhs, Expression* rhs, int line, int column)
        : Statement(line, column), lhs(lhs), rhs(rhs) {}

    ~AssignmentStatement() {
        delete lhs;
        delete rhs;
    }

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitAssignmentStatement(*this);
    }

    IdentifierExpression* getLhs() const { return lhs; }
    Expression* getRhs() const { return rhs; }

private:
    IdentifierExpression* lhs;
    Expression* rhs;
};

class ExpressionStatement : public Statement {
public:
    ExpressionStatement(Expression* expr, int line, int column)
        : Statement(line, column), expr(expr) {}

    ~ExpressionStatement() {
        delete expr;
    }

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitExpressionStatement(*this);
    }

    Expression* getExpr() const { return expr; }

private:
    Expression* expr;
};

class IfStatement : public Statement {
public:
    IfStatement(Expression* condition, Statement* thenBranch, Statement* elseBranch, int line, int column)
        : Statement(line, column), condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}

    ~IfStatement() {
        delete condition;
        delete thenBranch;
        delete elseBranch;
    }

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitIfStatement(*this);
    }

    Expression* getCondition() const { return condition; }
    Statement* getThenBranch() const { return thenBranch; }
    Statement* getElseBranch() const { return elseBranch; }

private:
    Expression* condition;
    Statement* thenBranch;
    Statement* elseBranch;
};

class WhileStatement : public Statement {
public:
    WhileStatement(Expression* condition, Statement* body, int line, int column)
        : Statement(line, column), condition(condition), body(body) {}

    ~WhileStatement() {
        delete condition;
        delete body;
    }

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitWhileStatement(*this);
    }

    Expression* getCondition() const { return condition; }
    Statement* getBody() const { return body; }

private:
    Expression* condition;
    Statement* body;
};

class ReturnStatement : public Statement {
public:
    ReturnStatement(Expression* value, int line, int column)
        : Statement(line, column), value(value) {}

    ~ReturnStatement() {
        delete value;
    }

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitReturnStatement(*this);
    }

    Expression* getValue() const { return value; }

private:
    Expression* value;
};

class BlockStatement : public Statement {
public:
    BlockStatement(const std::vector<Statement*>& statements, int line, int column)
        : Statement(line, column), statements(statements) {}

    ~BlockStatement() {
        for (auto* stmt : statements) {
            delete stmt;
        }
    }

    void accept(ASTNodeVisitor& visitor) override {
        visitor.visitBlockStatement(*this);
    }

    const std::vector<Statement*>& getStatements() const { return statements; }

private:
    std::vector<Statement*> statements;
};
