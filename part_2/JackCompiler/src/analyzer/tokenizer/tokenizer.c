//
// Created by yousif on 3/14/25.
//

#include "tokenizer.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "../../common/hash_table/hash_table.h"
#include "../../common/predefined_tables/predefined_tables.h"

static FILE *input_file;
static Token current_token;
static Token prev_token;
static hash_t token_table;

// initialize tokenizer
void tokenizer_init(const char *path) {
    input_file = fopen(path, "r");
    token_table = create_token_table();

    prev_token.t_name[0] = '\0';
    prev_token.type = T_END_OF_FILE;
}

// handle identifiers and keyword
void handle_identifier_and_keyword() {
    int c;
    int i = 0;

    while ((c = fgetc(input_file)) != EOF && isalnum(c)) {
        current_token.t_name[i++] = (char)c;
    }

    if (c != EOF) {
        ungetc(c, input_file);
    }
    current_token.t_name[i] = '\0';

    token_t *t = lookup(token_table, current_token.t_name);
    if (t == NULL) {
        current_token.type = T_IDENTIFIER;
    } else {
        current_token.type = *t;
    }
}

// handle integer constants
void handle_integer_constant() {
    int c;
    int i = 0;

    while ((c = fgetc(input_file)) != EOF && isdigit(c)) {
        current_token.t_name[i++] = (char)c;
    }

    if (c != EOF) {
        ungetc(c, input_file);
    }
    current_token.t_name[i] = '\0';
    current_token.type = T_INT_CONSTANT;
}

// handle string constants
void handle_string_constant() {
    int c;
    int i = 0;

    while ((c = fgetc(input_file)) != EOF && c != '"') {
        current_token.t_name[i++] = (char)c;
    }

    current_token.t_name[i] = '\0';
    current_token.type = T_STRING_CONSTANT;
}

// handle comments
void handle_comment() {
    int c;
    if (fgetc(input_file) == '/') {
        while ((c = fgetc(input_file)) != EOF && c != '\n');
    } else {
        int p = 0;
        while ((c = fgetc(input_file)) != EOF) {
            if (p == '*' && c == '/') {
                return;
            }
            p = c;
        }
    }
}

void advance() {
    int c;

    // skip white space
    while ((c = fgetc(input_file)) != EOF && isspace(c));

    // skip comments
    while (c != EOF && c == '/') {
        int t = fgetc(input_file);
        if (t == '*' || t == '/') {
            ungetc(t, input_file);
            handle_comment();
            while ((c = fgetc(input_file)) != EOF && isspace(c));
        } else {
            ungetc(t, input_file);
            break;
        }
    }

    if (isalpha(c)) {
        ungetc(c, input_file);
        handle_identifier_and_keyword();
        return;
    }

    if (isdigit(c)) {
        ungetc(c, input_file);
        handle_integer_constant();
        return;
    }

    if (c == '"') {
        handle_string_constant();
        return;
    }

    // handling symbols
    if (c != EOF) {
        current_token.t_name[0] = (char)c;
        current_token.t_name[1] = '\0';
        current_token.type = T_SYMBOL;
    } else {
        current_token.t_name[0] = '\0';
        current_token.type = T_END_OF_FILE;
    }
}

// store the current to token to be returned as the next token
void unget_token(Token t) { prev_token = t; }

// get the current token
Token get_current_token() { return current_token; }

// get the next token;
Token get_next_token() {
    if (prev_token.type == T_END_OF_FILE) {
        advance();
        return current_token;
    }

    Token t = prev_token;
    prev_token.type = T_END_OF_FILE;
    current_token = t;
    return t;
}

// clean up the current tokenizer
void tokenizer_destruct() {
    fclose(input_file);
    hash_t_free(token_table);
}

// look ahead without advancing
Token look_ahead() {
    const Token temp = current_token;
    const Token token = get_next_token();
    unget_token(token);
    current_token = temp;
    return token;
}

// set current token
void set_current_token(Token token) { current_token = token; }
