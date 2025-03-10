//
// Created by yousif on 3/2/25.
//

#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#include "../../include/data_types.h"

bool is_string_blank(const char *str);

void trim_string(char *str);

void remove_comment(char *str);

void get_command(char *command_buffer, const char *str);

void get_arg1(char *command_buffer, const char *str);

int get_arg2(const char *str);

enum command_type get_command_type(struct hash_table *table, const char *str);

char *get_mem_segment(struct hash_table *table, const char *str);

char get_operation(struct hash_table *table, const char *arg1);

char *get_program_name(char *str);

char *get_file_name(char const *str);

#endif  // PARSER_H
