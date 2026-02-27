#include <iostream>
#include <fstream>

#include "Token.h"
#include "Lexer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Uso: ./lonewolf <archivo>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Error: no se pudo abrir el archivo '" << argv[1] << "'" << std::endl;
        return 1;
    }

    Lexer lexer(file);

    Token token;
    do {
        token = lexer.getNextToken();
        std::cout << tokenTypeToString(token.type)
          << " : "
          << token.lexeme
          << std::endl;
    } while (token.type != TokenType::END_OF_FILE);

    return 0;
}
