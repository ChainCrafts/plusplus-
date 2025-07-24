#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    // Keywords
    TOKEN_NUMBER_KEYWORD, // 'number'
    TOKEN_WRITE,          // 'write'
    TOKEN_AND,            // 'and'
    TOKEN_NEWLINE,        // 'newline'
    TOKEN_REPEAT,         // 'repeat'
    TOKEN_TIMES,          // 'times'

    // Symbols and Operators
    TOKEN_SEMICOLON, // ';'
    TOKEN_ASSIGN,    // ':='
    TOKEN_INCREMENT, // '+='
    TOKEN_DECREMENT, // '-='
    TOKEN_LBRACE,    // '{'
    TOKEN_RBRACE,    // '}'
    TOKEN_MINUS,     // '-'

    // Literals and Identifiers
    TOKEN_IDENTIFIER,      // variable names
    TOKEN_NUMBER,          // integer constants
    TOKEN_STRING_CONSTANT, // string constants (e.g., "hello")

    // Special
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct
{
    TokenType type; // The token type
    char *lexeme;   // Text of the token
    int line;       // Line number
    int column;     // Column number
} Token;

/* Function declarations */
int get_next_char(FILE *file, int *line, int *column);
int peek_char(FILE *file);
bool is_keyword(const char *str);
bool is_identifier_start(char c);
bool is_identifier_char(char c);
Token get_next_token(FILE *file);

#endif /* LEXER_H */
