#pragma once

#include <vector>
#include "Lexer.h"
#include "ErrorCollector.h"
#include "Ast/AstNode.h"
#include "Ast/Expression.h"
#include "Ast/Statement.h"

class Parser {
public:
    Parser(Lexer& lexer, ErrorCollector& errorCollector);

    std::vector<Statement*> parse();

private:
    Lexer& lexer;
    ErrorCollector& errorCollector;
    
    Token currentToken;
    Token previousToken;

    void advance();

    Statement* statement();
    Expression* expression();
    Expression* comparison();
    Expression* term();
    Expression* unary();
    Expression* primary();

    bool check(TokenType type);
    bool match(TokenType type);
};
