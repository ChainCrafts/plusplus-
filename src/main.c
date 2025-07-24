#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Create a file path by adding extension to base name
 */
void create_filename(const char *base, const char *extension, char *buffer, size_t size);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: la <filename>\n");
        return 1;
    }

    // Create the .plus filename
    char plus_filename[256];
    create_filename(argv[1], ".plus", plus_filename, sizeof(plus_filename));

    // Open input file
    FILE *input = fopen(plus_filename, "r");
    if (!input)
    {
        perror("Error opening input file");
        return 1;
    }

    // Create the .lx output filename
    char output_filename[256];
    create_filename(argv[1], ".lx", output_filename, sizeof(output_filename));

    // Open output file
    FILE *output = fopen(output_filename, "w");
    if (!output)
    {
        perror("Error creating output file");
        fclose(input);
        return 1;
    }

    // Tokenize input
    Token token;
    bool has_error = false;
    while (1)
    {
        token = get_next_token(input);

        if (token.type == TOKEN_ERROR)
        {
            fprintf(stderr, "Lexical analysis failed. Exiting.\n");
            has_error = true;
            // Free token lexeme if allocated
            if (token.lexeme)
                free(token.lexeme);
            break;
        }

        if (token.type == TOKEN_EOF)
        {
            break;
        }

        // Print token to output file
        switch (token.type)
        {
        case TOKEN_NUMBER_KEYWORD:
            fprintf(output, "Keyword(number)\n");
            break;
        case TOKEN_WRITE:
            fprintf(output, "Keyword(write)\n");
            break;
        case TOKEN_AND:
            fprintf(output, "Keyword(and)\n");
            break;
        case TOKEN_NEWLINE:
            fprintf(output, "Keyword(newline)\n");
            break;
        case TOKEN_REPEAT:
            fprintf(output, "Keyword(repeat)\n");
            break;
        case TOKEN_TIMES:
            fprintf(output, "Keyword(times)\n");
            break;
        case TOKEN_SEMICOLON:
            fprintf(output, "EndOfLine\n");
            break;
        case TOKEN_ASSIGN:
            fprintf(output, "Operator(:=)\n");
            break;
        case TOKEN_INCREMENT:
            fprintf(output, "Operator(+=)\n");
            break;
        case TOKEN_DECREMENT:
            fprintf(output, "Operator(-=)\n");
            break;
        case TOKEN_LBRACE:
            fprintf(output, "OpenBlock\n");
            break;
        case TOKEN_RBRACE:
            fprintf(output, "CloseBlock\n");
            break;
        case TOKEN_IDENTIFIER:
            fprintf(output, "Identifier(%s)\n", token.lexeme);
            break;
        case TOKEN_NUMBER:
            fprintf(output, "IntConstant(%s)\n", token.lexeme);
            break;
        case TOKEN_STRING_CONSTANT:
            fprintf(output, "StringConstant(\"%s\")\n", token.lexeme);
            break;
        default:
            break;
        }

        if (token.lexeme)
            free(token.lexeme);
    }

    fclose(input);
    fclose(output);

    if (has_error)
    {
        fprintf(stderr, "Lexical analysis failed due to errors.\n");
        return 1;
    }
    else
    {
        printf("Lexical analysis completed successfully. Output written to %s\n", output_filename);
        return 0;
    }
}
