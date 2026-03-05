#pragma once

#include "Lexer.h"
#include "ErrorCollector.h"

class Parser {
public:
    Parser(Lexer& lexer, ErrorCollector& errorCollector);

    void parse();

private:
    Lexer& lexer;
    ErrorCollector& errorCollector;
    
    Token currentToken;
    Token previousToken;

    void advance();

    void statement();
    void expression();
    void term();
    void factor();
};
