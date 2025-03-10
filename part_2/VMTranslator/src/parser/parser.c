//
// Created by yousif on 3/2/25.
//
#include "parser.h"

#include <ctype.h>
#include <stdlib.h>

#include "../hash_table/hash_table.h"
#include "string.h"

// the buffer for the program name size
#define PROGRAM_NAME_SIZE 128

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

// get the command of a line
void get_command(char *command_buffer, const char *str) {
    while (!isspace(*str) && *str != '\0') {
        *command_buffer = *str;
        str++;
        command_buffer++;
    }
    *command_buffer = '\0';
}

// get the first argument of the command
void get_arg1(char *command_buffer, const char *str) {
    const char *start = strstr(str, " ") + 1;

    while (!isspace(*start)) {
        *command_buffer = *start;
        start++;
        command_buffer++;
    }
    *command_buffer = '\0';
}

// get the second argument of the command
int get_arg2(const char *str) {
    const char *end = str + strlen(str) - 1;
    while (end > str && isdigit(*end)) {
        end--;
    }

    int r = atoi(end);
    return r;
}

// accepts a command and returns its type
enum command_type get_command_type(struct hash_table *table, const char *str) {
    struct hash_table *result = hash_table_search(table, str);
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }
    return result->type;
}

// accepts the first argument and determines the memory segment of the command
char *get_mem_segment(struct hash_table *table, const char *str) {
    struct hash_table *result = hash_table_search(table, str);
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }
    return result->value;
}

// accepts the argument of an arithmetic command and returns the type of
// operation
char get_operation(struct hash_table *table, const char *arg1) {
    struct hash_table *result = hash_table_search(table, arg1);
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }
    return *result->value;
}

// return the program name without extension, it allocates heap memory
char *get_program_name(char *str) {
    char *extension = strrchr(str, '.');

    size_t length;

    if (extension == NULL) {
        length = strlen(str);
    } else {
        length = extension - str;
    }

    char *new_str = malloc(sizeof(char) * PROGRAM_NAME_SIZE);
    memcpy(new_str, str, length);
    new_str[length] = '\0';
    return new_str;
}

// return the file name without extension or full path
char *get_file_name(char const *str) {
    size_t length = strlen(str);

    size_t index = length;
    int count = 1;

    while (index != 0) {
        if (str[index] == '/') {
            index++;
            break;
        }
        index--;
        count++;
    }

    char *new_str = malloc(sizeof(char) * count);
    strcpy(new_str, str + index);

    char *extension = strrchr(new_str, '.');
    if (extension == NULL) {
        exit(EXIT_FAILURE);
    }
    *extension = '\0';

    return new_str;
}
