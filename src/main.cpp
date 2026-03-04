#include <iostream>
#include <fstream>

#include "Token.h"
#include "Lexer.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "[USO] ./lonewolf <archivo>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir el archivo '" << argv[1] << "'" << std::endl;
        return 1;
    }

    ErrorCollector errors;
    Lexer lexer(file, errors);

    Token token;
    do {
        token = lexer.getNextToken();

        std::cout << tokenTypeToString(token.type)
          << " : "
          << token.lexeme
          << std::endl;

    } while (token.type != TokenType::END_OF_FILE);

    if (errors.hasErrors()) {
        std::cout << "\nErrores encontrados:\n";

        for (const auto& err : errors.getErrors()) {
            std::cout << "Linea "
                    << err.line
                    << ", Columna "
                    << err.column
                    << " -> "
                    << err.message
                    << std::endl;
        }
    }

    return 0;
}
