//
// Created by yousif on 3/14/25.
//

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>


// element of the hash table
typedef struct elem_t {
    char *key;
    void *value;
    struct elem_t *next;
} elem_t;

// struct for the hash table
typedef struct hash_t {
    elem_t *array;
    size_t array_size;
    size_t value_size;
} hash_t;

void hash_t_init(hash_t *t, size_t size, size_t n);

void hash_t_insert(hash_t t, char *key, void *value);

void *lookup(hash_t t, const char *key);

void hash_t_free(hash_t t);

char *new_string(const char *str);

#endif //HASH_TABLE_H
