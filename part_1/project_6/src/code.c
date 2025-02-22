#include <stdlib.h>
#include "../include/parser.h"
#include "../include/code.h"

#define BINARY_STRING_SIZE 15

// convert a decimal string to a binary string of length BINARY_STRING_SIZE
char *decimal_to_binary(char string[]) {
    int decimal = atoi(string);
    char *binary_string = malloc(sizeof(char) * BINARY_STRING_SIZE);
    char bit;

    for (int i = BINARY_STRING_SIZE - 1; i >= 0; i--) {
        if (decimal % 2) {
            bit = '1';
        } else {
            bit = '0';
        }

        decimal /= 2;
        binary_string[i] = bit;
    }
    return binary_string;
}

// return the binary code for dest
char *dest_code(char string[], s_hash_table table) {
    s_element *elem = search(table, string);

    if (elem == NULL) {
        exit(-1);
    }

    return elem->value;
}

// return the code for comp
char *comp_code(char string[], s_hash_table table) {
    s_element *elem = search(table, string);

    if (elem == NULL) {
        exit(-1);
    }

    return elem->value;
}

// return the code for jump
char *jump_code(char string[], s_hash_table table) {
    s_element *elem = search(table, string);

    if (elem == NULL) {
        exit(-1);
    }

    return elem->value;
}






















