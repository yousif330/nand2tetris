//
// Created by yousif on 3/19/25.
//

// this module contain functions for handling expressions

#include "compile_expressions.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../../../common/hash_table/hash_table.h"
#include "../../../common/predefined_tables/predefined_tables.h"
#include "../../tokenizer/tokenizer.h"

static FILE *output_file;
static hash_t keyword_table;
static hash_t operator_table;

void compile_term();

// set the value for the output file
void set_output_file(FILE *out) {
    output_file = out;
    keyword_table = create_keyword_table();
    operator_table = create_operator_table();
}

// compile identifier
void compile_identifier() {
    const Token token = get_current_token();
    if (isdigit(*token.t_name)) {
        exit(EXIT_FAILURE);
    }

    print_tag("identifier", token.t_name);
}

// compile var name
// identifier('[' expression ']')?
void compile_var_name() {
    compile_identifier();

    if (look_ahead().t_name[0] == '[') {
        get_next_token();
        process("[");
        print_tag("symbol", "[");

        get_next_token();
        compile_expression();

        get_next_token();
        process("]");
        print_tag("symbol", "]");
    }
}

// compile bi operator
void compile_op() {
    const Token token = get_current_token();
    const token_t *t = lookup(operator_table, token.t_name);

    if (t != NULL && *t == BI_OPERATOR) {
        print_tag("symbol", token.t_name);
        return;
    }

    exit(EXIT_FAILURE);
}

// compile unary operator
void compile_unary_op() {
    const Token token = get_current_token();

    if (token.t_name[0] == '-' || token.t_name[0] == '~') {
        print_tag("symbol", token.t_name);
        return;
    }

    exit(EXIT_FAILURE);
}

// compile keyword constant
void compile_keyword_constant() {
    const Token token = get_current_token();
    const token_t *t = lookup(keyword_table, token.t_name);

    if (t != NULL &&
        (*t == K_THIS || *t == K_NULL || *t == K_TRUE || *t == K_FALSE)) {
        print_tag("keyword", token.t_name);
        return;
    }

    exit(EXIT_FAILURE);
}

// compile parenthesised expression
// '(' expression ')' | '(' unary term ')'
void compile_parenthesised_expression() {
    print_tag("symbol", "(");
    const Token token = get_next_token();

    if (token.t_name[0] == '~' || token.t_name[0] == '-') {
        compile_unary_op(get_current_token().t_name);

        get_next_token();
        compile_term();
    } else {
        compile_expression();
    }

    get_next_token();
    process(")");
    print_tag("symbol", ")");
}

// compile a single term in an expression
void compile_term() {
    Token token = get_current_token();

    if (token.type == T_INT_CONSTANT) {
        print_tag("integerConstant", token.t_name);
    }

    if (token.type == T_STRING_CONSTANT) {
        print_tag("stringConstant", token.t_name);
    }

    if (token.type == T_KEYWORD) {
        compile_keyword_constant(token.t_name);
    }

    if (token.type == T_IDENTIFIER) {
        const Token next = look_ahead();
        if (next.t_name[0] == '(' || next.t_name[0] == '.') {
            compile_function_call();
        } else {
            compile_var_name();
        }
    }

    if (token.t_name[0] == '(') {
        compile_parenthesised_expression();
    }
}

// compile expression
void compile_expression() {
    // return if expression is empty
    if (get_current_token().t_name[0] == ')') {
        unget_token(get_current_token());
        return;
    }

    compile_term();

    Token t = get_next_token();
    while (t.t_name[0] != ';' && t.t_name[0] != ')' && t.t_name[0] != ']' &&
           t.t_name[0] != ',') {
        compile_op(get_current_token().t_name);

        get_next_token();
        compile_term();

        t = get_next_token();
    }

    unget_token(t);
}

// compile a comma separated list of expressions
// expression(',' expression ')?
void compile_expression_list() {
    process("(");
    print_tag("symbol", "(");

    get_next_token();
    compile_expression();

    while (get_next_token().t_name[0] != ')') {
        process(",");
        print_tag("symbol", ",");

        get_next_token();
        compile_expression();
    }

    process(")");
    print_tag("symbol", ")");
}

// compile function call
void compile_function_call() {
    compile_identifier();

    if (look_ahead().t_name[0] == '.') {
        get_next_token();
        process(".");
        print_tag("symbol", ".");

        get_next_token();
        compile_identifier();
    }

    get_next_token();
    compile_expression_list();
}

// process compare the current token with the expected token
void process(char const *expected) {
    if (strcmp(get_current_token().t_name, expected) != 0) {
        exit(EXIT_FAILURE);
    }
}

// print tag
void print_tag(char const *token_type, char const *value) {
    fprintf(output_file, "<%s>%s</%s>\n", token_type, value, token_type);
}

// clean up memory
void cleanup_primitive_compilation_engine() {
    hash_t_free(keyword_table);
    hash_t_free(operator_table);
}
