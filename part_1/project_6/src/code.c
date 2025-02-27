#include "../include/code.h"
#include "../include/parser.h"

#define BINARY_STRING_SIZE 16

// convert a decimal string to a binary string
char *decimal_to_binary(char string[]) {
    int decimal = atoi(string);
    char *binary_string = malloc(sizeof(char) * BINARY_STRING_SIZE);
    char bit;

    for (int i = BINARY_STRING_SIZE - 2; i >= 0; i--) {
        if (decimal % 2) {
            bit = '1';
        } else {
            bit = '0';
        }

        decimal /= 2;
        binary_string[i] = bit;
    }
    binary_string[BINARY_STRING_SIZE - 1] = '\0';
    return binary_string;
}

//convert a an integer to binary string
char *int_to_binary(int value) {
    char *binary_string = malloc(sizeof(char) * BINARY_STRING_SIZE);
    char bit;

    for (int i = BINARY_STRING_SIZE - 2; i >= 0; i--) {
        if (value % 2) {
            bit = '1';
        } else {
            bit = '0';
        }

        value /= 2;
        binary_string[i] = bit;
    }
    binary_string[BINARY_STRING_SIZE - 1] = '\0';
    return binary_string;

}

// check if string is numeric
bool is_numeric(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

// return the binary code for dest
char *dest_code(char string[], s_symbol_table table) {
    s_element *elem = search(table, string);

    if (elem == NULL) {
        exit(-1);
    }

    return elem->value;
}

// return the code for comp
char *comp_code(char string[], s_symbol_table table) {
    s_element *elem = search(table, string);

    if (elem == NULL) {
        exit(-1);
    }

    return elem->value;
}

// return the code for jump
char *jump_code(char string[], s_symbol_table table) {
    s_element *elem = search(table, string);

    if (elem == NULL) {
        exit(-1);
    }

    return elem->value;
}
