#pragma once
#include <string>
#include <unordered_map>

enum class TokenType {
    // Keywords
    IF,          // if
    ELSE,        // else
    WHILE,       // while
    RETURN,      // return
    // FUNCTION,
    // LET,
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
        // Keywords
        case TokenType::IF:             return "IF";
        case TokenType::ELSE:           return "ELSE";
        case TokenType::WHILE:          return "WHILE";
        case TokenType::RETURN:         return "RETURN";
        // Identifiers & literals
        case TokenType::IDENTIFIER:     return "IDENTIFIER";
        case TokenType::NUMBER:         return "NUMBER";
        // Operators
        case TokenType::ASSIGN:         return "ASSIGN";
        case TokenType::PLUS:           return "PLUS";
        case TokenType::MINUS:          return "MINUS";
        case TokenType::STAR:           return "STAR";
        case TokenType::SLASH:          return "SLASH";
        // Delimiters
        case TokenType::SEMICOLON:      return "SEMICOLON";
        case TokenType::LPAREN:         return "LPAREN";
        case TokenType::RPAREN:         return "RPAREN";
        case TokenType::LBRACE:         return "LBRACE";
        case TokenType::RBRACE:         return "RBRACE";
        // Operadores compuestos
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
