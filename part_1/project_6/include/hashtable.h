#ifndef _HASH_TABLE_
#define _HASH_TABLE_

// a struct for the elements of the hash table
typedef struct s_element {
    char *key;
    char *value;
} s_element;

// struct for the hash table
typedef struct s_hash_table{
    s_element *array;
    int size;
    int length;
} s_hash_table;


// function for creating a hash table and initlizing it with null
s_hash_table create_hash_table(int size);

// resize the hash table to double of the old size
s_hash_table resize_hash_table(s_hash_table table);

// function for inserting in a hash table
s_hash_table insert(s_hash_table table, char *key, char *value);

// return the elemet holding the key value, return null otherwise
s_element *search(s_hash_table table, char *key);

// function for freeing all the memory used by the hash table
void delete_hash_table(s_hash_table table);

// generate the comp instruction set in a hash table
s_hash_table comp_instruction_set();

// generate the jump instuction set in a hash table
s_hash_table jump_instruction_set();

// generate the dest instruction set in a hash table
s_hash_table dest_instruction_set();

#endif
