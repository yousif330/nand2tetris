//
// Created by yousif on 3/14/25.
//

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

typedef enum token_t {
    T_KEYWORD,
    T_IDENTIFIER,
    T_INT_CONSTANT,
    T_SYMBOL,
    T_STRING_CONSTANT,
    T_END_OF_FILE
} token_t;

typedef enum keyword_t {
    K_CLASS,
    K_METHOD,
    K_FUNCTION,
    K_CONSTRUCTOR,
    K_INT,
    K_CHAR,
    K_BOOLEAN,
    K_VOID,
    K_VAR,
    K_STATIC,
    K_FILED,
    K_LET,
    K_DO,
    K_WHILE,
    K_IF,
    K_ELSE,
    K_RETURN,
    K_TRUE,
    K_FALSE,
    K_NULL,
    K_THIS,
} keyword_t;

typedef enum {
    BI_OPERATOR,
    UNARY_OPERATOR,
} operator_t;

typedef struct token {
    token_t type;
    char t_name[256];
} Token;

#endif  // DATA_TYPES_H
