//
// Created by yousif on 3/2/25.
//

#ifndef CODE_WRITER_H
#define CODE_WRITER_H

#include <stdio.h>

#include "../../include/data_types.h"

void write_push_pop(char *arg1, int arg2, enum command_type command, FILE *out);

void write_static_push_pop(char *arg1, int arg2, FILE *out,
                           enum command_type command);

void write_arithmetic(char op, FILE *out, char *current_function);

void write_infinite_loop(FILE *out);

void write_function(FILE *out, char *arg1, int arg2);

void write_label(FILE *out, char *arg1, char *current_function);

void write_if(FILE *out, char *arg1, char *current_function);

void write_goto(FILE *out, char *arg1, char *current_function);

void write_call(FILE *out, char *arg1, int arg2, char *current_function,
                int call_count);

void write_return(FILE *out);

void write_bootstrap(FILE *out);

#endif  // CODE_WRITER_H
