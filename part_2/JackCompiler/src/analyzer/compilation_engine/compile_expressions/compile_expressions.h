//
// Created by yousif on 3/19/25.
//

#ifndef COMPILE_EXPRESSION_H
#define COMPILE_EXPRESSION_H

#include <stdio.h>

void set_output_file(FILE *out);

void compile_identifier();

void compile_expression();

void compile_var_name();

void compile_function_call();

void process(char const *expected);

void print_tag(char const *token_type, char const *value);

void cleanup_primitive_compilation_engine();

#endif  // COMPILE_EXPRESSION_H
