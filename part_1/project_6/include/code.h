#ifndef _CODE_
#define _CODE_

#include "hashtable.h"

// convert a decimal string to binary
char *decimal_to_binary(char buffer[]);

// return the binary code for dest
char *dest_code(char string[], s_hash_table table);

// return the code for comp
char *comp_code(char string[], s_hash_table table);

// return the code for jump
char *jump_code(char string[], s_hash_table table);

#endif
