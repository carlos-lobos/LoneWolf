#pragma once
#include <string>

enum class TokenType {
    // Keywords
    FUNCTION,
    LET,
    RETURN,
    PRINT,

    // Types
    INT_TYPE,

    // Identifiers & literals
    IDENTIFIER,
    NUMBER,

    // Operators
    PLUS,
    MINUS,
    STAR,
    SLASH,
    EQUAL,
    ARROW,

    // Delimiters
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    SEMICOLON,

    END_OF_FILE,
    INVALID
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token()
        : type(TokenType::END_OF_FILE),
          lexeme(""),
          line(0),
          column(0) {}
};
