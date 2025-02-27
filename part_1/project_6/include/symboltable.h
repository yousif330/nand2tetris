#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_

// a struct for the elements of the hash table
typedef struct s_element {
    char *key;
    char *value;
} s_element;

// struct for the hash table
typedef struct s_symbol_table {
    s_element *array;
    int length;
} s_symbol_table;

// struct to hold predefined tables
typedef struct s_predefined_symbols {
    s_symbol_table dest_table;
    s_symbol_table comp_table;
    s_symbol_table jump_table;
} s_predefined_symbols;

// function for creating a hash table and initlizing it with null
s_symbol_table create_symbol_table(int size);

// function for inserting in a hash table
s_symbol_table insert(s_symbol_table table, char *key, char *value);

// return the elemet holding the key value, return null otherwise
s_element *search(s_symbol_table table, char *key);

// generate the comp instruction set in a hash table
s_symbol_table comp_instruction_set();

// generate the jump instuction set in a hash table
s_symbol_table jump_instruction_set();

// generate the dest instruction set in a hash table
s_symbol_table dest_instruction_set();

// build all the predefined symbol tables
s_predefined_symbols build_symbol_tables();

// free the predefined symbol tables
void delete_symbol_tables(s_predefined_symbols symbol_tables);

#endif
