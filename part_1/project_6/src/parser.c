#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../include/parser.h"

#define SYMBOL_BUFFER_SIZE 1024
#define DEST_BUFFER_SIZE 10
#define COMP_BUFFER_SIZE 10
#define JUMP_BUFFER_SIZE 10

// open the assembly file
FILE *open_file(char* file_path) {
    return fopen(file_path, "r");
}

// fetch a line from a file, return null if it reach the end
char *fetch_line(char buffer[], int buffer_size, FILE *input_file) {
    return fgets(buffer, buffer_size, input_file);
}


// check if line is comment
bool is_comment(char buffer[]) {
    if (strstr(buffer, "//")) {
        return true;
    }
    return false;
}

// check if line is empty
bool is_blank(char buffer[]) {
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n') {
            return false;
        }
    }
    return true;
}

// check if line is skippable
bool is_skippable(char buffer[]) {
    if (is_comment(buffer) || is_blank(buffer)) {
        return true;
    }
    return false;
}

// advance to the next line
char *advance(char buffer[], int buffer_size, FILE *input_file) {
    return fgets(buffer, buffer_size, input_file);
}

// return the type of the instruction
instruction_t check_instruction_type(char buffer[]) { 
    if (strstr(buffer, "@")) {
        return A_INSTRUCTION;
    } else if (strstr(buffer, "(")) {
        return L_INSTRUCTION;
    } else {
        return C_INSTRUCTION;
    }
}

// copy a string until the specified end character
void copy_string(char *dest, char *src, char end) {
    int i;
    for (i = 0; src[i] != end && src[i] != '\0' && src[i] != '\n'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

// return the symbol of type A or L instructions
char *symbol(char buffer[]) {
    char *symbol_buffer = (char *)malloc(sizeof(char) * SYMBOL_BUFFER_SIZE);

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '@' || buffer[i] == '(') {
            copy_string(symbol_buffer, buffer + i + 1, ')');
            break;
        }
    }
    return symbol_buffer;
}

// return the dest of type c instruction
char *dest(char buffer[]) {
    char *dest_buffer = (char *)malloc(sizeof(char) * DEST_BUFFER_SIZE);
    
    // check if there is dest in the instruction
    if (strstr(buffer, "=") == NULL) {
        dest_buffer[0] = '\0';
        return dest_buffer;
    }

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] != ' ' && buffer[i] != '\t') {
            copy_string(dest_buffer, buffer + i, '=');
            break;
        }
    }
    return dest_buffer;
}

// return the jump of type c instruction
char *jump(char buffer[]) {
    char *jump_buffer = (char *)malloc(sizeof(char) * JUMP_BUFFER_SIZE);

    // check if there is jump in the instruction
    if (strstr(buffer, ";") == NULL) {
        jump_buffer[0] = '\0';
        return jump_buffer;
    }

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ';') {
            copy_string(jump_buffer, buffer + i + 1, ' ');
            break;
        }
    }
    return jump_buffer;
}

// return the comp of type c instructions
char *comp(char buffer[]) {
    char *comp_buffer = (char *)malloc(sizeof(char) * COMP_BUFFER_SIZE);

    if (strstr(buffer, "=") != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == '=') {
                copy_string(comp_buffer, buffer + i + 1, ';');
                break;
            }
        }
    } else {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] != ' ' && buffer[i] != '\t') {
                copy_string(comp_buffer, buffer + i, ';');
                break;
            }
        }
    }

    return comp_buffer;
}

// copy a string until a pattern
void copy_until_pattern(char *dest, char *src, char *pattern) {
    char *pointer_to_pattern = strstr(src, pattern);

    if (pointer_to_pattern == NULL) {
        return;
    }

    int len = strlen(src) - strlen(pointer_to_pattern);
    strncpy(dest, src, len);
    dest[len] = '\0';
}


// generate the output file name from the input file name
char *output_file_name(char *input_file_name) {
    char *output_file_name = malloc(sizeof(char) * strlen(input_file_name) + 2);


    copy_until_pattern(output_file_name, input_file_name, ".asm");
    strcat(output_file_name, ".hack");
    return output_file_name;
}

// open output file
FILE *open_output_file(char *file_path) {
    char *str = output_file_name(file_path);
    FILE *output_file = fopen(str, "w");
    free(str);

    return output_file;
}





















