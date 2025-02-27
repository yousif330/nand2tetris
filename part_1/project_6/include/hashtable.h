#ifndef _HASH_TABLE_
#define _HASH_TABLE_


typedef struct s_table_int {
    char *identifier;
    int address;
    struct s_table_int *next;
} s_table_int;

// function to create a hash table
s_table_int *create_table();

// insert at hash table
void insert_at_table(s_table_int *table, char *key, int value);

// search for a element in a hash table
// return the a pointer to the element if found, return null otherwise
s_table_int *search_table(s_table_int *table, char *key);

// free the hash table
void delete_hash_table(s_table_int table[]);

// create a hash table with a predefined symbols
s_table_int *create_table_with_predefined_symbols();

#endif
