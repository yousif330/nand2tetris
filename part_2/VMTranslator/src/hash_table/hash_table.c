//
// Created by yousif on 3/2/25.
//

#include "hash_table.h"

#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 1024

struct hash_table *hash_table_init() {
    struct hash_table *table =
        calloc(HASH_TABLE_SIZE, sizeof(struct hash_table));
    if (table == NULL) {
        exit(EXIT_FAILURE);
    }
    return table;
}

long hash_function(const char *key) {
    long hash = 5381;
    int c;

    while ((c = (int)*key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_TABLE_SIZE;
}

// chain elements in case of collusion
void hash_table_chain(struct hash_table *elem, char *key, char *value,
                      enum command_type command) {
    struct hash_table *new_elem = malloc(sizeof(struct hash_table));

    new_elem->key = key;
    new_elem->value = value;
    new_elem->type = command;
    new_elem->next = NULL;

    while (elem->next) {
        elem = elem->next;
    }
    elem->next = new_elem;
}

void hash_table_insert(struct hash_table *table, char *key, char *value,
                       enum command_type command) {
    long index = hash_function(key);

    if (table[index].next != NULL) {
        hash_table_chain(table, key, value, command);
    } else {
        table[index].key = key;
        table[index].value = value;
        table[index].type = command;
    }
}

// a function to free individual chains
void hash_table_free_chain(struct hash_table *elem) {
    struct hash_table *prev = NULL;
    while (elem) {
        prev = elem;
        elem = elem->next;
        free(prev);
    }
}

void hash_table_free(struct hash_table *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        if (table[i].next != NULL) {
            hash_table_free_chain(table[i].next);
        }
    }
    free(table);
}

struct hash_table *hash_table_search(struct hash_table *table,
                                     const char *key) {
    long index = hash_function(key);
    struct hash_table *elem = &table[index];

    while (elem != NULL) {
        if (strcmp(elem->key, key) == 0) {
            return elem;
        }
        elem = elem->next;
    }
    return NULL;
}

// generate hash table with predefined commands and memory segments
struct hash_table *hash_table_command_set_init() {
    struct hash_table *table = hash_table_init();

    hash_table_insert(table, "push", NULL, C_PUSH);
    hash_table_insert(table, "pop", NULL, C_POP);
    hash_table_insert(table, "add", "+", C_ARITHMETIC);
    hash_table_insert(table, "sub", "-", C_ARITHMETIC);
    hash_table_insert(table, "neg", "n", C_ARITHMETIC);
    hash_table_insert(table, "eq", "e", C_ARITHMETIC);
    hash_table_insert(table, "gt", "g", C_ARITHMETIC);
    hash_table_insert(table, "lt", "l", C_ARITHMETIC);
    hash_table_insert(table, "not", "!", C_ARITHMETIC);
    hash_table_insert(table, "and", "&", C_ARITHMETIC);
    hash_table_insert(table, "or", "|", C_ARITHMETIC);
    hash_table_insert(table, "function", NULL, C_FUNCTION);
    hash_table_insert(table, "label", NULL, C_LABEL);
    hash_table_insert(table, "if-goto", NULL, C_IF);
    hash_table_insert(table, "goto", NULL, C_GOTO);
    hash_table_insert(table, "call", NULL, C_CALL);
    hash_table_insert(table, "return", NULL, C_RETURN);

    hash_table_insert(table, "local", "LCL", C_NULL);
    hash_table_insert(table, "argument", "ARG", C_NULL);
    hash_table_insert(table, "this", "THIS", C_NULL);
    hash_table_insert(table, "that", "THAT", C_NULL);
    hash_table_insert(table, "pointer", "P", C_NULL);
    hash_table_insert(table, "temp", "t", C_NULL);
    hash_table_insert(table, "constant", "C", C_NULL);
    hash_table_insert(table, "static", "S", C_NULL);

    return table;
}
