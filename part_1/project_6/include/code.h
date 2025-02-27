#ifndef _CODE_
#define _CODE_


#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "symboltable.h"

// convert a decimal string to binary
char *decimal_to_binary(char buffer[]);

//convert a an integer to binary string
char *int_to_binary(int value);

// return the binary code for dest
char *dest_code(char string[], s_symbol_table table);

// return the code for comp
char *comp_code(char string[], s_symbol_table table);

// return the code for jump
char *jump_code(char string[], s_symbol_table table);

// check if string is numeric
bool is_numeric(char *str);

#endif
