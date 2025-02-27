#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"

#define HASH_ARRAY_SIZE 256

// function to create a hash table
s_table_int *create_table() {
    return calloc(HASH_ARRAY_SIZE, sizeof(s_table_int));
}

// djb2 hash function
int hash_function(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_ARRAY_SIZE;
}

// chain elements if collusion happens
void chain(s_table_int *element, char *key, int value) {
    s_table_int *new_element = malloc(sizeof(s_table_int));

    new_element->address = value;
    new_element->identifier = key;
    new_element->next = NULL;

    s_table_int *p = element;
    while (p->next) {
        p = p->next;
    }

    p->next = new_element;
}

// insert at hash table
void insert_at_table(s_table_int *table, char *key, int value) {
    int index = hash_function(key);

    if (table[index].identifier == NULL) {
        table[index].identifier = key;
        table[index].address = value;
    } else {
        chain(&table[index], key, value);
    }
}

// search for a element in a hash table
// return the a pointer to the element if found, return null otherwise
s_table_int *search_table(s_table_int *table, char *key) {
    int index = hash_function(key);
    s_table_int *p = &table[index];

    if (p->identifier != NULL) {
        while (p) {
            if (strcmp(p->identifier, key) == 0) {
                return p;
            }
            p = p->next;
        }
    }

    return NULL;
}

// free the hash table
void delete_hash_table(s_table_int table[]) {
    for (int i = 0; i < HASH_ARRAY_SIZE; i++) {
        if (table[i].identifier != NULL) {
            s_table_int *curr, *prev;
            free(table[i].identifier);
            curr = table[i].next;

            while (curr) {
                prev = curr;
                curr = curr->next;

                free(prev->identifier);
                free(prev);
            }
        }
    }
    free(table);
}

// convert a string literal to a heap string
char *new_string(char *str) {
    int len = strlen(str);
    char *new = malloc(sizeof(char) * len + 1);

    return strcpy(new, str);
}

// create a hash table with a predefined symbols
s_table_int *create_table_with_predefined_symbols() {
    s_table_int *table = create_table();

    // create virtual registers
    insert_at_table(table, new_string("R0"), 0);
    insert_at_table(table, new_string("R1"), 1);
    insert_at_table(table, new_string("R2"), 2);
    insert_at_table(table, new_string("R3"), 3);
    insert_at_table(table, new_string("R4"), 4);
    insert_at_table(table, new_string("R5"), 5);
    insert_at_table(table, new_string("R6"), 6);
    insert_at_table(table, new_string("R7"), 7);
    insert_at_table(table, new_string("R8"), 8);
    insert_at_table(table, new_string("R9"), 9);
    insert_at_table(table, new_string("R10"), 10);
    insert_at_table(table, new_string("R11"), 11);
    insert_at_table(table, new_string("R12"), 12);
    insert_at_table(table, new_string("R13"), 13);
    insert_at_table(table, new_string("R14"), 14);
    insert_at_table(table, new_string("R15"), 15);
    
    insert_at_table(table, new_string("SP"), 0);
    insert_at_table(table, new_string("LCL"), 1);
    insert_at_table(table, new_string("ARG"), 2);
    insert_at_table(table, new_string("THIS"), 3);
    insert_at_table(table, new_string("THAT"), 4);

    // input output devices
    insert_at_table(table, new_string("SCREEN"), 16384);
    insert_at_table(table, new_string("KBD"), 24576);

    return table;
}
    


























