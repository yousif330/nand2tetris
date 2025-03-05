//
// Created by yousif on 3/2/25.
//

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

enum command_type {
    C_NULL = 0,
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL,
};

struct hash_table {
    struct hash_table *next;
    char *key;
    char *value;
    enum command_type type;
};


#endif //DATA_TYPES_H
