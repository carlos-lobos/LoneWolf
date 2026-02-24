#include "Lexer.h"

Lexer::Lexer(std::istream& input)
    : input(input), currentChar(0), line(1), column(0)
{
}

Token Lexer::getNextToken() {
    Token t;
    t.type = TokenType::END_OF_FILE;
    t.lexeme = "";
    t.line = line;
    t.column = column;
    return t;
}
