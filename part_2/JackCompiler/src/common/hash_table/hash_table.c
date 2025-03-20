//
// Created by yousif on 3/14/25.
//

#include "hash_table.h"

#include <stdlib.h>
#include <string.h>

// initialize the hash table
void hash_t_init(hash_t *t, size_t size, size_t n) {
    t->array = calloc(n, sizeof(elem_t));
    t->array_size = n;
    t->value_size = size;
}

// hash function : DJB2
size_t hash_function(const char *str) {
    size_t hash = 5381;
    int c;

    while ((c = (int)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// function for chaining elements
void chain(elem_t *elem, char *key, void *value, size_t size) {
    // creating a new slot for the element
    elem_t *new_elem = malloc(sizeof(elem_t));
    new_elem->key = key;
    new_elem->next = NULL;
    new_elem->value = malloc(size);
    memcpy(new_elem->value, value, size);

    // chaining the new element
    elem_t *p = elem;
    while (p->next) {
        p = p->next;
    }
    p->next = new_elem;
}

// insert an element, chain if collusion happens
void hash_t_insert(hash_t t, char *key, void *value) {
    size_t index = hash_function(key) % t.array_size;

    if (t.array[index].key == NULL) {
        t.array[index].key = key;
        t.array[index].value = malloc(t.value_size);
        memcpy(t.array[index].value, value, t.value_size);
    } else {
        chain(&t.array[index], key, value, t.value_size);
    }
}

// search an element
void *lookup(hash_t t, const char *key) {
    size_t index = hash_function(key) % t.array_size;
    elem_t *p = &t.array[index];

    while (p && p->key && strcmp(p->key, key) != 0) {
        p = p->next;
    }

    if (p == NULL) {
        return NULL;
    }
    return p->value;
}

// a function to free a chain
void hash_t_free_chain(elem_t *elem) {
    elem_t *p = NULL;
    while (elem) {
        p = elem;
        elem = elem->next;
        free(p->value);
        free(p->key);
        free(p);
    }
}

// function to free the hash table
void hash_t_free(hash_t t) {
    for (int i = 0; i < t.array_size; i++) {
        if (t.array[i].key != NULL) {
            free(t.array[i].value);
            free(t.array[i].key);

            if (t.array[i].next) {
                hash_t_free_chain(t.array[i].next);
            }
        }
    }
    free(t.array);
}

// copy a string literal to the heap
char *new_string(const char *str) {
    size_t size = strlen(str) + 1;
    char *new = malloc(sizeof(char) * size);
    strcpy(new, str);
    return new;
}
