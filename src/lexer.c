#include "lexer.h"
#include <string.h>
#include <ctype.h>
#include <string.h>

/* 1.read one character at a time from the file, and keep track
of line and column numbers for error reporting.*/
int get_next_char(FILE *file, int *line, int *column)
{
    int c = fgetc(file);

    if (c == '\n')
    {
        (*line)++;
        *column = 0;
    }
    else
    {
        (*column)++;
    }

    return c;
}

/*2. Peeking ahead without consuming the char
Sometimes you need to look at the next character without advancing
the file pointer (e.g., for := or += detection).*/
int peek_char(FILE *file)
{
    int c = fgetc(file);
    if (c != EOF)
    {
        ungetc(c, file);
    }
    return c;
}

/* 3. Checking if a string is a keyword
To differentiate identifiers from keywords,
we need a function to check if a string matches any keyword: */
bool is_keyword(const char *str)
{
    const char *keywords[] = {
        "number", "write", "and", "newline", "repeat", "times"};
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < num_keywords; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

/*4. Checking if a character is valid for identifiers
Identifier rules: start with a letter,
continue with letters, digits or underscore.*/
bool is_identifier_start(char c)
{
    return (isalpha(c));
}

bool is_identifier_char(char c)
{
    return (isalnum(c) || c == '_');
}

Token get_next_token(FILE *file)
{
    static int line = 1;
    static int col = 0;
    int ch;

    // Skip whitespace and track line/column
    while ((ch = fgetc(file)) != EOF)
    {
        col++;

        if (ch == ' ' || ch == '\t' || ch == '\r')
        {
            continue;
        }
        else if (ch == '\n')
        {
            line++;
            col = 0;
            // Don't return a token for newlines, just skip them
            continue;
        }
        else
        {
            break;
        }
    }

    if (ch == EOF)
    {
        return (Token){TOKEN_EOF, strdup("EOF"), line, col};
    }

    // Identifiers and Keywords
    if (isalpha(ch))
    {
        char buffer[64];
        int len = 0;
        int start_col = col;

        do
        {
            buffer[len++] = ch;
            ch = fgetc(file);
            col++;
        } while (isalnum(ch) || ch == '_');

        buffer[len] = '\0';
        ungetc(ch, file);
        col--;

        // Check for keywords
        if (strcmp(buffer, "number") == 0)
            return (Token){TOKEN_NUMBER_KEYWORD, strdup(buffer), line, start_col};
        if (strcmp(buffer, "write") == 0)
            return (Token){TOKEN_WRITE, strdup(buffer), line, start_col};
        if (strcmp(buffer, "and") == 0)
            return (Token){TOKEN_AND, strdup(buffer), line, start_col};
        if (strcmp(buffer, "newline") == 0)
            return (Token){TOKEN_NEWLINE, strdup(buffer), line, start_col};
        if (strcmp(buffer, "repeat") == 0)
            return (Token){TOKEN_REPEAT, strdup(buffer), line, start_col};
        if (strcmp(buffer, "times") == 0)
            return (Token){TOKEN_TIMES, strdup(buffer), line, start_col};

        return (Token){TOKEN_IDENTIFIER, strdup(buffer), line, start_col};
    }

    // Integer Constants
    if (isdigit(ch))
    {
        char buffer[64];
        int len = 0;
        int start_col = col;

        do
        {
            buffer[len++] = ch;
            ch = fgetc(file);
            col++;
        } while (isdigit(ch));

        buffer[len] = '\0';
        ungetc(ch, file);
        col--;

        return (Token){TOKEN_NUMBER, strdup(buffer), line, start_col};
    }

    // String Constants
    if (ch == '"')
    {
        char buffer[256];
        int len = 0;
        int start_col = col;

        while ((ch = fgetc(file)) != '"' && ch != EOF)
        {
            if (ch == '\n')
            {
                fprintf(stderr, "Unterminated string at line %d\n", line);
                return (Token){TOKEN_ERROR, NULL, line, start_col};
            }
            buffer[len++] = ch;
        }

        if (ch != '"')
        {
            fprintf(stderr, "Error: Unterminated string constant at line %d, column %d\n", line, start_col);
            return (Token){TOKEN_ERROR, strdup("Unterminated string"), line, start_col};
        }

        buffer[len] = '\0';
        return (Token){TOKEN_STRING_CONSTANT, strdup(buffer), line, start_col};
    }

    // Comments (ignore content between * ... *)
    if (ch == '*')
    {
        int start_col = col;
        while ((ch = fgetc(file)) != EOF)
        {
            col++;
            if (ch == '\n')
            {
                line++;
                col = 0;
            }
            if (ch == '*')
                break;
        }

        // Check if comment was closed properly
        if (ch == EOF)
        {
            fprintf(stderr, "Error: Unclosed comment at line %d, column %d\n", line, start_col);
            return (Token){TOKEN_ERROR, strdup("Unclosed comment"), line, start_col};
        }

        // Skip comment and get next token
        return get_next_token(file);
    }

    // Operators and Symbols
    int start_col = col;

    switch (ch)
    {
    case ':':
        if ((ch = fgetc(file)) == '=')
        {
            col++;
            return (Token){TOKEN_ASSIGN, strdup(":="), line, start_col};
        }
        else
        {
            ungetc(ch, file);
            col--;
            fprintf(stderr, "Lexical error at line %d, column %d: unexpected character ':'\n", line, start_col);
            return (Token){TOKEN_ERROR, strdup(":"), line, start_col};
        }
        break;

    case '+':
        if ((ch = fgetc(file)) == '=')
        {
            col++;
            return (Token){TOKEN_INCREMENT, strdup("+="), line, start_col};
        }
        else
        {
            ungetc(ch, file);
            col--;
            fprintf(stderr, "Lexical error at line %d, column %d: unexpected character '+'\n", line, start_col);
            return (Token){TOKEN_ERROR, strdup("+"), line, start_col};
        }
        break;

    case '-':
        if ((ch = fgetc(file)) == '=')
        {
            col++;
            return (Token){TOKEN_DECREMENT, strdup("-="), line, start_col};
        }
        else
        {
            ungetc(ch, file);
            col--;
            return (Token){TOKEN_MINUS, strdup("-"), line, start_col};
        }

    case '{':
        return (Token){TOKEN_LBRACE, strdup("{"), line, start_col};
    case '}':
        return (Token){TOKEN_RBRACE, strdup("}"), line, start_col};
    case ';':
        return (Token){TOKEN_SEMICOLON, strdup(";"), line, start_col};
    }

    // Unknown character
    fprintf(stderr, "Lexical error at line %d, column %d: unexpected character '%c'\n", line, col, ch);

    // Create a string with the unexpected character
    char unexpected[2] = {ch, '\0'};
    return (Token){TOKEN_ERROR, strdup(unexpected), line, start_col};
}
