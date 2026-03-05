#include <iostream>
#include <fstream>

// Para lectura del archivo en memoria
#include <vector>
#include <string>

#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "[USO] ./lonewolf <archivo>" << std::endl;
        return 1;
    }


    // Abrir el archivo fuente para lectura
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir el archivo '" << argv[1] << "'" << std::endl;
        return 1;
    }


    // INI :: lectura del archivo en memoria
    std::vector<std::string> sourceLines;
    std::string lineText;

    while (std::getline(file, lineText)) {
        sourceLines.push_back(lineText);
    }

    file.clear();  // limpiar flags EOF
    file.seekg(0); // volver al inicio
    // FIN :: lectura del archivo en memoria



    // Inicializar el ErrorCollector para recopilar errores durante el análisis léxico y sintáctico
    ErrorCollector errors;



    // =========================
    // FASE 1 — LEXER (debug)
    // =========================
    Lexer lexer(file, errors);

    Token token;
    do {
        token = lexer.getNextToken();

        std::cout << tokenTypeToString(token.type)
          << " : "
          << token.lexeme
          << std::endl;

    } while (token.type != TokenType::END_OF_FILE);

    file.clear();       // limpiar flags EOF
    file.seekg(0);      // volver al inicio



    // =========================
    // FASE 2 — PARSER
    // =========================

    Lexer parserLexer(file, errors);
    Parser parser(parserLexer, errors);

    parser.parse();



    // =========================
    // MOSTRAR ERRORES
    // =========================

    if (errors.hasErrors()) {
        std::cout << "\nErrores encontrados:\n\n";

        for (const auto& err : errors.getErrors()) {

            std::cout << argv[1]
                    << ":" << err.line
                    << ":" << err.column
                    << " \033[31merror:\033[0m "
                    << err.message
                    << "\n\n";

            if (err.line > 0 && err.line <= sourceLines.size()) {

                const std::string& codeLine = sourceLines[err.line - 1];

                std::cout << codeLine << std::endl;

                for (int i = 1; i < err.column; i++)
                    std::cout << " ";

                std::cout << "^" << std::endl;
            }

            std::cout << std::endl;
        }
    }


    // Retornar 0 para indicar que el programa terminó correctamente
    return 0;
}
