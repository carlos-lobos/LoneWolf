#pragma once
#include <string>

enum class TokenType {
    // Keywords
    // FUNCTION,
    // LET,
    // RETURN,
    // PRINT,

    // Types
    // INT_TYPE,

    // Identifiers & literals
    IDENTIFIER,
    NUMBER,

    // Operators
    ASSIGN,      // =
    PLUS,        // +
    MINUS,       // -
    STAR,        // *
    SLASH,       // /
    // ARROW,

    // Delimiters
    SEMICOLON,   // ;
    LPAREN,      // (
    RPAREN,      // )
    LBRACE,      // {
    RBRACE,      // }

    // Operadores compuestos
    EQUAL,        // ==
    NOT_EQUAL,    // !=
    LESS,         // <
    LESS_EQUAL,   // <=
    GREATER,      // >
    GREATER_EQUAL, // >=

    END_OF_FILE // \n
    // INVALID
};

inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER:     return "IDENTIFIER";
        case TokenType::NUMBER:         return "NUMBER";
        case TokenType::ASSIGN:         return "ASSIGN";
        case TokenType::PLUS:           return "PLUS";
        case TokenType::MINUS:          return "MINUS";
        case TokenType::STAR:           return "STAR";
        case TokenType::SLASH:          return "SLASH";
        case TokenType::SEMICOLON:      return "SEMICOLON";
        case TokenType::LPAREN:         return "LPAREN";
        case TokenType::RPAREN:         return "RPAREN";
        case TokenType::LBRACE:         return "LBRACE";
        case TokenType::RBRACE:         return "RBRACE";
        case TokenType::EQUAL:          return "EQUAL";
        case TokenType::NOT_EQUAL:      return "NOT_EQUAL";
        case TokenType::LESS:           return "LESS";
        case TokenType::LESS_EQUAL:     return "LESS_EQUAL";
        case TokenType::GREATER:        return "GREATER";
        case TokenType::GREATER_EQUAL:  return "GREATER_EQUAL";
        case TokenType::END_OF_FILE:    return "EOF";
        default:                        return "UNKNOWN";
    }
}

/*struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token()
        : type(TokenType::END_OF_FILE),
          lexeme(""),
          line(0),
          column(0) {}
};*/

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    // Constructor por defecto
    Token()
        : type(TokenType::END_OF_FILE),
          lexeme(""),
          line(0),
          column(0) {}

    // Constructor con parámetros
    Token(TokenType type,
          const std::string& lexeme,
          int line,
          int column)
        : type(type),
          lexeme(lexeme),
          line(line),
          column(column) {}
};