#pragma once

#include <istream>
#include <string>
#include "Token.h"

class Lexer {
public:
    explicit Lexer(std::istream& input);

    Token getNextToken();

private:
    std::istream& input;
    int currentChar;
    int line;
    int column;

    void advance();
    void skipWhitespace();
    Token number();
    Token identifier();
    int peek();
};
