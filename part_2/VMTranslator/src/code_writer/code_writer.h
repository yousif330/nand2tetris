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

void write_arithmetic(char op, FILE *out, char *program_name);

void write_infinite_loop(FILE *out);

#endif  // CODE_WRITER_H
