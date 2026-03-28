#include "Parser.h"

Parser::Parser(Lexer& lexer, ErrorCollector& errorCollector)
    : lexer(lexer), errorCollector(errorCollector)
{
    advance();
}

void Parser::advance() {
    previousToken = currentToken;
    currentToken = lexer.getNextToken();
}

std::vector<Statement*> Parser::parse() {
    std::vector<Statement*> statements;
    while (currentToken.type != TokenType::END_OF_FILE) {
        statements.push_back(statement());
    }
    return statements;
}

bool Parser::check(TokenType type) {
    if (currentToken.type == type) return true;
    return false;
}

bool Parser::match(TokenType type) {
    if (!check(type)) return false;
    advance();
    return true;
}

Statement* Parser::statement() {
    if (match(TokenType::IF)) {
        int line = previousToken.line;
        int column = previousToken.column;

        if (!match(TokenType::LPAREN)) {
            errorCollector.addError("Expected '(' after 'if'", line, column);
        }

        Expression* condition = expression();

        if (!match(TokenType::RPAREN)) {
            errorCollector.addError("Expected ')' after condition", currentToken.line, currentToken.column);
        }

        Statement* thenBranch = statement();
        Statement* elseBranch = nullptr;

        if (match(TokenType::ELSE)) {
            elseBranch = statement();
        }

        return new IfStatement(condition, thenBranch, elseBranch, line, column);
    }

    if (match(TokenType::WHILE)) {
        int line = previousToken.line;
        int column = previousToken.column;

        if (!match(TokenType::LPAREN)) {
            errorCollector.addError("Expected '(' after 'while'", line, column);
        }

        Expression* condition = expression();

        if (!match(TokenType::RPAREN)) {
            errorCollector.addError("Expected ')' after condition", currentToken.line, currentToken.column);
        }

        Statement* body = statement();

        return new WhileStatement(condition, body, line, column);
    }

    if (match(TokenType::RETURN)) {
        int line = previousToken.line;
        int column = previousToken.column;

        Expression* value = nullptr;
        if (!check(TokenType::SEMICOLON)) {
            value = expression();
        }

        if (!match(TokenType::SEMICOLON)) {
            errorCollector.addError("Expected ';' after return value", previousToken.line, previousToken.column + previousToken.lexeme.length());
        }

        return new ReturnStatement(value, line, column);
    }

    if (match(TokenType::LBRACE)) {
        int line = previousToken.line;
        int column = previousToken.column;

        std::vector<Statement*> statements;
        while (!check(TokenType::RBRACE) && !check(TokenType::END_OF_FILE)) {
            statements.push_back(statement());
        }

        if (!match(TokenType::RBRACE)) {
            errorCollector.addError("Expected '}' after block", currentToken.line, currentToken.column);
        }

        return new BlockStatement(statements, line, column);
    }

    if (currentToken.type == TokenType::IDENTIFIER) {
        int line = currentToken.line;
        int column = currentToken.column;
        std::string identifierName = currentToken.lexeme;

        advance();

        if (match(TokenType::ASSIGN)) {
            Expression* rhs = expression();

            if (!match(TokenType::SEMICOLON)) {
                errorCollector.addError("Expected ';'", previousToken.line, previousToken.column + previousToken.lexeme.length());
            }

            IdentifierExpression* lhs = new IdentifierExpression(identifierName, line, column);
            return new AssignmentStatement(lhs, rhs, line, column);
        }
    }

    int line = currentToken.line;
    int column = currentToken.column;
    Expression* expr = expression();

    if (!match(TokenType::SEMICOLON)) {
        errorCollector.addError("Expected ';'", previousToken.line, previousToken.column + previousToken.lexeme.length());
    }

    return new ExpressionStatement(expr, line, column);
}

Expression* Parser::expression() {
    Expression* expr = comparison();

    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        std::string op = previousToken.lexeme;
        Expression* right = comparison();
        Expression* left = expr;
        expr = new BinaryExpression(left, op, right, left->getLine(), left->getColumn());
    }

    return expr;
}

Expression* Parser::comparison() {
    Expression* expr = term();

    while (
        match(TokenType::GREATER) ||
        match(TokenType::GREATER_EQUAL) ||
        match(TokenType::LESS) ||
        match(TokenType::LESS_EQUAL) ||
        match(TokenType::EQUAL) ||
        match(TokenType::NOT_EQUAL)
    ) {
        std::string op = previousToken.lexeme;
        Expression* right = term();
        Expression* left = expr;
        expr = new BinaryExpression(left, op, right, left->getLine(), left->getColumn());
    }

    return expr;
}

Expression* Parser::term() {
    Expression* expr = unary();

    while (match(TokenType::STAR) || match(TokenType::SLASH)) {
        std::string op = previousToken.lexeme;
        Expression* right = unary();
        Expression* left = expr;
        expr = new BinaryExpression(left, op, right, left->getLine(), left->getColumn());
    }

    return expr;
}

Expression* Parser::unary() {
    if (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        std::string op = previousToken.lexeme;
        int line = previousToken.line;
        int column = previousToken.column;
        Expression* operand = unary();
        return new UnaryExpression(op, operand, line, column);
    }

    return primary();
}

Expression* Parser::primary() {
    if (match(TokenType::NUMBER)) {
        return new LiteralExpression(previousToken.lexeme, previousToken.line, previousToken.column);
    }

    if (match(TokenType::STRING)) {
        return new LiteralExpression(previousToken.lexeme, previousToken.line, previousToken.column);
    }

    if (match(TokenType::IDENTIFIER)) {
        return new IdentifierExpression(previousToken.lexeme, previousToken.line, previousToken.column);
    }

    if (match(TokenType::LPAREN)) {
        int line = previousToken.line;
        int column = previousToken.column;
        Expression* inner = expression();

        if (!match(TokenType::RPAREN)) {
            errorCollector.addError("Expected ')'", currentToken.line, currentToken.column);
        }

        return new GroupedExpression(inner, line, column);
    }

    errorCollector.addError("Unexpected token in expression", currentToken.line, currentToken.column);
    advance();
    return new LiteralExpression("error", currentToken.line, currentToken.column);
}
