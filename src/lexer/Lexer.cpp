#include <cctype>
#include "Lexer.h"

Lexer::Lexer(std::istream& input)
    : input(input), currentChar(0), line(1), column(0)
{
    advance();  // leer primer carácter
}

void Lexer::advance() {
    currentChar = input.get();

    if (currentChar == '\n') {
        line++;
        column = 0;
    } else {
        column++;
    }
}

void Lexer::skipWhitespace() {
    while (std::isspace(currentChar)) {
        advance();
    }
}

Token Lexer::identifier() {
    std::string lexeme;
    int startLine = line;
    int startColumn = column;

    while (std::isalnum(currentChar) || currentChar == '_') {
        lexeme += static_cast<char>(currentChar);
        advance();
    }

    Token t;
    t.type = TokenType::IDENTIFIER;
    t.lexeme = lexeme;
    t.line = startLine;
    t.column = startColumn;

    return t;
}

Token Lexer::number() {
    std::string lexeme;
    int startLine = line;
    int startColumn = column;
    bool hasDot = false;

    while (std::isdigit(currentChar) || currentChar == '.') {

        if (currentChar == '.') {
            if (hasDot) break;  // evitar múltiples puntos
            hasDot = true;
        }

        lexeme += static_cast<char>(currentChar);
        advance();
    }

    Token t;
    t.type = TokenType::NUMBER;
    t.lexeme = lexeme;
    t.line = startLine;
    t.column = startColumn;

    return t;
}

Token Lexer::getNextToken() {

    while (currentChar != EOF) {

        if (std::isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (std::isalpha(currentChar) || currentChar == '_') {
            return identifier();
        }

        if (std::isdigit(currentChar)) {
            return number();
        }

        //-- INI :: Manejo de operadores compuestos (antes de los operadores simples) --//
        // == o =
        if (currentChar == '=') {
            int startLine = line;
            int startColumn = column;

            std::string lexeme;

            if (peek() == '=') {
                lexeme += static_cast<char>(currentChar); // es '='
                advance(); // consume '='
                lexeme += static_cast<char>(currentChar); // es '=='
                advance(); // consume segundo '='
                return Token(TokenType::EQUAL, lexeme, startLine, startColumn);
            } else {
                lexeme += static_cast<char>(currentChar); // es '='
                advance();
                return Token(TokenType::ASSIGN, lexeme, startLine, startColumn);
            }
        }

        // !=
        if (currentChar == '!') {
            int startLine = line;
            int startColumn = column;

            std::string lexeme;

            if (peek() == '=') {
                lexeme += static_cast<char>(currentChar); // es '!'
                advance();
                lexeme += static_cast<char>(currentChar); // es '!='
                advance();
                return Token(TokenType::NOT_EQUAL, lexeme, startLine, startColumn);
            }
        }

        // <= o <
        if (currentChar == '<') {
            int startLine = line;
            int startColumn = column;

            std::string lexeme;

            if (peek() == '=') {
                lexeme += static_cast<char>(currentChar); // es '<'
                advance();
                lexeme += static_cast<char>(currentChar); // es '<='
                advance();
                return Token(TokenType::LESS_EQUAL, lexeme, startLine, startColumn);
            } else {
                lexeme += static_cast<char>(currentChar); // es '<'
                advance();
                return Token(TokenType::LESS, lexeme, startLine, startColumn);
            }
        }

        // >= o >
        if (currentChar == '>') {
            int startLine = line;
            int startColumn = column;

            std::string lexeme;

            if (peek() == '=') {
                lexeme += static_cast<char>(currentChar); // es '>'
                advance();
                lexeme += static_cast<char>(currentChar); // es '>='
                advance();
                return Token(TokenType::GREATER_EQUAL, lexeme, startLine, startColumn);
            } else {
                lexeme += static_cast<char>(currentChar); // es '>'
                advance();
                return Token(TokenType::GREATER, lexeme, startLine, startColumn);
            }
        }
        //-- FIN :: Manejo de operadores compuestos (antes de los operadores simples) --//

        //-- Preparo las variables para usarlas en los tokens de 1 solo caracter (operadores simples) --//
        int startLine = line;
        int startColumn = column;
        char c = static_cast<char>(currentChar);

        switch (currentChar) {
            /*case '=':
                advance();
                return Token{TokenType::ASSIGN, std::string(1, c), startLine, startColumn};*/
                
            case '+':
                advance();
                return Token{TokenType::PLUS, std::string(1, c), startLine, startColumn};

            case '-':
                advance();
                return Token{TokenType::MINUS, std::string(1, c), startLine, startColumn};

            case '*':
                advance();
                return Token{TokenType::STAR, std::string(1, c), startLine, startColumn};

            case '/':
                advance();
                return Token{TokenType::SLASH, std::string(1, c), startLine, startColumn};

            case ';':
                advance();
                return Token{TokenType::SEMICOLON, std::string(1, c), startLine, startColumn};

            case '(':
                advance();
                return Token{TokenType::LPAREN, std::string(1, c), startLine, startColumn};

            case ')':
                advance();
                return Token{TokenType::RPAREN, std::string(1, c), startLine, startColumn};

            case '{':
                advance();
                return Token{TokenType::LBRACE, std::string(1, c), startLine, startColumn};

            case '}':
                advance();
                return Token{TokenType::RBRACE, std::string(1, c), startLine, startColumn};

        }

        //-- Salteo cualquier otra cosa --//
        advance();
    }

    Token t;
    t.type = TokenType::END_OF_FILE;
    t.lexeme = "";
    t.line = line;
    t.column = column;

    return t;
}

int Lexer::peek() {
    return input.peek();
}
