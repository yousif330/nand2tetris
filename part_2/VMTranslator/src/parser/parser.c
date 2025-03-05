//
// Created by yousif on 3/2/25.
//
#include "parser.h"

#include <ctype.h>
#include <stdlib.h>

#include "../hash_table/hash_table.h"
#include "string.h"

#define PROGRAM_NAME_SIZE 64

bool is_string_blank(const char *str) {
    while (*str) {
        if (!isspace(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

void trim_string(char *str) {
    char *start = str;
    while (isspace(*start)) {
        start++;
    }

    if (*start == '\0') {
        return;
    }

    char *end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) {
        end--;
    }

    memmove(str, start, end - start + 1);

    str[end - start + 1] = '\0';
}

void remove_comment(char *str) {
    char *start = strstr(str, "//");
    if (start != NULL) {
        *start = '\0';
    }
}

void get_command(char *command_buffer, const char *str) {
    while (!isspace(*str)) {
        *command_buffer = *str;
        str++;
        command_buffer++;
    }
    *command_buffer = '\0';
}

void get_arg1(char *command_buffer, const char *str) {
    // skip the arg1
    const char *start = strstr(str, " ") + 1;

    while (!isspace(*start)) {
        *command_buffer = *start;
        start++;
        command_buffer++;
    }
    *command_buffer = '\0';
}

int get_arg2(const char *str) {
    while (!isdigit(*str)) {
        str++;
    }
    return atoi(str);
}

enum command_type get_command_type(struct hash_table *table, const char *str) {
    struct hash_table *result = hash_table_search(table, str);
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }
    return result->type;
}

char *get_mem_segment(struct hash_table *table, const char *str) {
    struct hash_table *result = hash_table_search(table, str);
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }
    return result->value;
}

char get_operation(struct hash_table *table, const char *arg1) {
    struct hash_table *result = hash_table_search(table, arg1);
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }
    return *result->value;
}

char *get_program_name(char *str) {
    char *extension = strrchr(str, '.');
    if (extension == NULL) {
        exit(EXIT_FAILURE);
    }

    size_t length = extension - str + 1;
    char *new_str = malloc(sizeof(char) * PROGRAM_NAME_SIZE);
    memcpy(new_str, str, length);
    new_str[length] = '\0';
    return new_str;
}
