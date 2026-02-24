#include <iostream>
#include "Token.h"

int main() {
    Token t;
    t.type = TokenType::IDENTIFIER;
    t.lexeme = "test";
    t.line = 1;
    t.column = 1;

    std::cout << "Token creado: " << t.lexeme << std::endl;
    return 0;
}
