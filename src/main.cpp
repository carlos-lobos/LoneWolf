#include <iostream>
#include <fstream>

#include "Token.h"
#include "Lexer.h"

int main() {
    Token t;
    t.type = TokenType::IDENTIFIER;
    t.lexeme = "test";
    t.line = 1;
    t.column = 1;

    std::cout << "Token creado: " << t.lexeme << std::endl;


    std::ifstream file("examples/test.lw");
    Lexer lexer(file);

    Token token;
    do {
        token = lexer.getNextToken();
        std::cout << token.lexeme << std::endl;
    } while (token.type != TokenType::END_OF_FILE);

    
    return 0;
}
