#include "Parser.h"

// Constructor del Parser, inicializa el lexer y el errorCollector, y obtiene el primer token
Parser::Parser(Lexer& lexer, ErrorCollector& errorCollector)
    : lexer(lexer), errorCollector(errorCollector)
{
    advance();
}

// advance() obtiene el siguiente token del lexer y lo asigna a currentToken
void Parser::advance() {
    previousToken = currentToken;
    currentToken = lexer.getNextToken();
}

// parse() lee los tokens hasta que se llegue al final del archivo, y llama a statement() para procesar cada declaración o instrucción
void Parser::parse() {
    while (currentToken.type != TokenType::END_OF_FILE) {
        statement();
    }
}

// statement() maneja la sintaxis de una declaración o instrucción, en este caso una asignación o una expresión seguida de un punto y coma
void Parser::statement() {

    // int startLine = currentToken.line;
    // int startColumn = currentToken.column;

    if (currentToken.type == TokenType::IDENTIFIER) {

        advance();

        if (currentToken.type == TokenType::ASSIGN) {

            advance();
            expression();

            if (currentToken.type == TokenType::SEMICOLON) {
                advance();
            } else {
                errorCollector.addError(
                    "Expected ';'",
                    previousToken.line,
                    previousToken.column + previousToken.lexeme.length()
                );
            }

        }

    } else {

        expression();

        if (currentToken.type == TokenType::SEMICOLON) {
            advance();
        } else {
            errorCollector.addError(
                "Expected ';'",
                previousToken.line,
                previousToken.column + previousToken.lexeme.length()
            );
        }

    }
}

// expression() maneja la sintaxis de una expresión, en este caso una suma o resta de términos
void Parser::expression() {

    term();

    while (
        currentToken.type == TokenType::PLUS ||
        currentToken.type == TokenType::MINUS
    ) {

        advance();
        term();
    }
}

// term() maneja la sintaxis de un término, en este caso una multiplicación o división de factores
void Parser::term() {

    factor();

    while (
        currentToken.type == TokenType::STAR ||
        currentToken.type == TokenType::SLASH
    ) {

        advance();
        factor();
    }
}

// factor() maneja la sintaxis de un factor, en este caso un número, una cadena, un identificador o una expresión entre paréntesis
void Parser::factor() {

    if (
        currentToken.type == TokenType::NUMBER ||
        currentToken.type == TokenType::STRING ||
        currentToken.type == TokenType::IDENTIFIER
    ) {
        advance();
        return;
    }

    if (currentToken.type == TokenType::LPAREN) {

        advance();
        expression();

        if (currentToken.type == TokenType::RPAREN) {
            advance();
        } else {
            errorCollector.addError(
                "Expected ')'",
                currentToken.line,
                currentToken.column
            );
        }

        return;
    }

    errorCollector.addError(
        "Unexpected token in expression",
        currentToken.line,
        currentToken.column
    );

    advance();
}

