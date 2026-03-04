#include <cctype>
#include "Lexer.h"

const std::unordered_map<std::string, TokenType> Lexer::keywords = {
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"while", TokenType::WHILE},
    {"return", TokenType::RETURN}
};

Lexer::Lexer(std::istream& input, ErrorCollector& errorCollector)
    : input(input),
      errorCollector(errorCollector),
      currentChar(0),
      line(1),
      column(0)
{
    advance();
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

    auto it = keywords.find(lexeme);
    if (it != keywords.end()) {
        return Token(it->second, lexeme, startLine, startColumn);
    }

    return Token(TokenType::IDENTIFIER, lexeme, startLine, startColumn);

    /* Alternativamente:
    Token t;
    t.type = TokenType::IDENTIFIER;
    t.lexeme = lexeme;
    t.line = startLine;
    t.column = startColumn;

    return t;
    */
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

void Lexer::addCurrentCharToLexeme(Token& token) {
    token.lexeme += static_cast<char>(currentChar);
    advance();
}

Token Lexer::getNextToken() {

    while (currentChar != EOF) {

        if (std::isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (currentChar == '"') {
            return stringLiteral();
        }

        if (std::isalpha(currentChar) || currentChar == '_') {
            return identifier();
        }

        if (std::isdigit(currentChar)) {
            return number();
        }

        Token token;
        TokenType type;

        //-- INI :: Manejo de operadores compuestos (antes de los operadores simples) --//
        // == o =
        if (currentChar == '=') {
            int startLine = line;
            int startColumn = column;

            if (peek() == '=') {
                addCurrentCharToLexeme(token); // consume '=' + advance()
                type = TokenType::EQUAL;  // ==
            } else {
                type = TokenType::ASSIGN; // =
            }

            addCurrentCharToLexeme(token); // consume '=' + advance()
            token.type = type;
            token.line = startLine;
            token.column = startColumn;

            return token;
        }

        // != o !
        if (currentChar == '!') {
            int startLine = line;
            int startColumn = column;

            if (peek() == '=') {
                addCurrentCharToLexeme(token); // consume '!' + advance()
                type = TokenType::NOT_EQUAL;   // !=
            } else {
                type = TokenType::BANG;        // !
            }

            addCurrentCharToLexeme(token); // consume '!' o '=' + advance()
            token.type = type;
            token.line = startLine;
            token.column = startColumn;

            return token;
        }

        // <= o <
        if (currentChar == '<') {
            int startLine = line;
            int startColumn = column;

            if (peek() == '=') {
                addCurrentCharToLexeme(token); // consume '<' + advance()
                type = TokenType::LESS_EQUAL;  // <=
            } else {
                type = TokenType::LESS;        // <
            }

            addCurrentCharToLexeme(token); // consume '<' o '=' + advance()
            token.type = type;
            token.line = startLine;
            token.column = startColumn;

            return token;
        }

        // >= o >
        if (currentChar == '>') {
            int startLine = line;
            int startColumn = column;

            if (peek() == '=') {
                addCurrentCharToLexeme(token); // consume '>' + advance()
                type = TokenType::GREATER_EQUAL;  // >=
            } else {
                type = TokenType::GREATER;        // >
            }

            addCurrentCharToLexeme(token); // consume '>' o '=' + advance()
            token.type = type;
            token.line = startLine;
            token.column = startColumn;

            return token;
        }

        // "//" o "/*" o "/"
        if (currentChar == '/') {

            if (peek() == '/') {
                skipLineComment();
                continue;
            }

            if (peek() == '*') {
                skipBlockComment();
                continue;
            }

            int startLine = line;
            int startColumn = column;

            addCurrentCharToLexeme(token); // consume '/' + advance()
            type = TokenType::SLASH;       // /

            token.type = type;
            token.line = startLine;
            token.column = startColumn;

            return token;
        }
        //-- FIN :: Manejo de operadores compuestos (antes de los operadores simples) --//

        //-- Preparo las variables para usarlas en los tokens de 1 solo caracter (operadores simples) --//
        int startLine = line;
        int startColumn = column;
        char c = static_cast<char>(currentChar);

        switch (currentChar) {
            case '+':
                advance();
                return Token{TokenType::PLUS, std::string(1, c), startLine, startColumn};

            case '-':
                advance();
                return Token{TokenType::MINUS, std::string(1, c), startLine, startColumn};

            case '*':
                advance();
                return Token{TokenType::STAR, std::string(1, c), startLine, startColumn};

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

        //-- Error ante un caracter no reconocido --//
        advance();

        std::string message = std::string("Unexpected character: ") + c;

        errorCollector.addError(message,
                        startLine,
                        startColumn);

        return Token(TokenType::ERROR,
             message,
             startLine,
             startColumn);
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

void Lexer::skipLineComment() {
    // consumir "//"
    advance();
    advance();

    while (currentChar != '\n' && currentChar != EOF) {
        advance();
    }
}

void Lexer::skipBlockComment() {
    // consumir "/*"
    advance();
    advance();

    while (currentChar != EOF) {

        if (currentChar == '*' && peek() == '/') {
            advance(); // consume '*'
            advance(); // consume '/'
            return;
        }

        advance();
    }
}

Token Lexer::stringLiteral() {
    int startLine = line;
    int startColumn = column;

    std::string lexeme;
    advance(); // consumir la comilla inicial "

    while (currentChar != '"' && currentChar != EOF) {

        if (currentChar == '\n') {
            errorCollector.addError("Unterminated string literal",
                        startLine,
                        startColumn);
            
            return Token(TokenType::ERROR,
                    "Unterminated string literal",
                    startLine,
                    startColumn);
        }

        if (currentChar == '\\') {  // escape sequence
            advance();

            switch (currentChar) {
                case 'n': lexeme += '\n'; break;
                case 't': lexeme += '\t'; break;
                case '"': lexeme += '"';  break;
                case '\\': lexeme += '\\'; break;
                default:
                    lexeme += static_cast<char>(currentChar);
                    break;
            }
        } else {
            lexeme += static_cast<char>(currentChar);
        }

        advance();
    }

    if (currentChar == '"') {
        advance(); // consumir comilla final
        return Token(TokenType::STRING, lexeme, startLine, startColumn);
    }

    errorCollector.addError("Unterminated string literal",
                        startLine,
                        startColumn);
    
    return Token(TokenType::ERROR,
             "Unterminated string literal",
             startLine,
             startColumn);

    return Token(TokenType::END_OF_FILE, "", startLine, startColumn);
}
