#ifndef _PARSER_
#define _PARSER_

#include <stdio.h>
#include <stdbool.h>

// a data type for the type of the instruction
typedef enum {
    A_INSTRUCTION,
    C_INSTRUCTION,
    L_INSTRUCTION
} instruction_t;

// open the assembly file
FILE *open_file(char* file_path);

// fetch a line from the file
char *fetch_line(char buffer[], int buffer_size, FILE *input_file);

// check if line is skippable
bool is_skippable(char buffer[]);

// advance to the next line if the current line is a comment or empty
char *advance(char buffer[], int buffer_size, FILE *input_file);

// return the type of the instruction
instruction_t check_instruction_type(char buffer[]);

// return the symbol of type A or L instructions
char *symbol(char buffer[]);

// return the dest of type c instruction
char *dest(char buffer[]);

// return the jump of type c instruction
char *jump(char buffer[]);

// return the comp of type c instructions
char *comp(char buffer[]);

#endif
