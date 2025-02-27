#include "../include/symboltable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function for creating a hash table and initlizing it with null
s_symbol_table create_symbol_table(int size) {
    s_element *array = calloc(size, sizeof(s_element));
    s_symbol_table table = {array, 0};
    return table;
}

// function for inserting in a hash table
s_symbol_table insert(s_symbol_table table, char *key, char *value) {

    table.array[table.length].value = value;
    table.array[table.length].key = key;
    table.length++;

    return table;
}

// return the elemet holding the key value, return null otherwise
s_element *search(s_symbol_table table, char *key) {
    for (int i = 0; i < table.length; i++) {
        if (strcmp(table.array[i].key, key) == 0) {
            return &table.array[i];
        }
    }
    return NULL;
}

// generate the comp instruction set in a hash table
s_symbol_table comp_instruction_set() {
    s_symbol_table table = create_symbol_table(50);

    table = insert(table, "0", "0101010");
    table = insert(table, "1", "0111111");
    table = insert(table, "-1", "0111010");
    table = insert(table, "D", "0001100");
    table = insert(table, "A", "0110000");
    table = insert(table, "!D", "0001101");
    table = insert(table, "!A", "0110001");
    table = insert(table, "-D", "0001111");
    table = insert(table, "-A", "0110011");
    table = insert(table, "D+1", "0011111");
    table = insert(table, "A+1", "0110111");
    table = insert(table, "D-1", "0001110");
    table = insert(table, "A-1", "0110010");
    table = insert(table, "D+A", "0000010");
    table = insert(table, "D-A", "0010011");
    table = insert(table, "A-D", "0000111");
    table = insert(table, "D&A", "0000000");
    table = insert(table, "D|A", "0010101");
    table = insert(table, "M", "1110000");
    table = insert(table, "!M", "1110001");
    table = insert(table, "-M", "1110011");
    table = insert(table, "M+1", "1110111");
    table = insert(table, "M-1", "1110010");
    table = insert(table, "D+M", "1000010");
    table = insert(table, "D-M", "1010011");
    table = insert(table, "M-D", "1000111");
    table = insert(table, "D&M", "1000000");
    table = insert(table, "D|M", "1010101");

    return table;
}

// generate the jump instuction set in a hash table
s_symbol_table jump_instruction_set() {
    s_symbol_table table = create_symbol_table(9);

    table = insert(table, "", "000");
    table = insert(table, "JGT", "001");
    table = insert(table, "JEQ", "010");
    table = insert(table, "JGE", "011");
    table = insert(table, "JLT", "100");
    table = insert(table, "JNE", "101");
    table = insert(table, "JLE", "110");
    table = insert(table, "JMP", "111");

    return table;
}

// generate the dest instruction set in a hash table
s_symbol_table dest_instruction_set() {
    s_symbol_table table = create_symbol_table(9);

    table = insert(table, "", "000");
    table = insert(table, "M", "001");
    table = insert(table, "D", "010");
    table = insert(table, "DM", "011");
    table = insert(table, "A", "100");
    table = insert(table, "AM", "101");
    table = insert(table, "AD", "110");
    table = insert(table, "ADM", "111");

    return table;
}

// build all predefined tables
s_predefined_symbols build_symbol_tables() {
    s_predefined_symbols symbol_tables;

    symbol_tables.dest_table = dest_instruction_set();
    symbol_tables.comp_table = comp_instruction_set();
    symbol_tables.jump_table = jump_instruction_set();

    return symbol_tables;
}

// free the predefined symbol tables
void delete_symbol_tables(s_predefined_symbols symbol_tables) {
    free(symbol_tables.dest_table.array);
    free(symbol_tables.comp_table.array);
    free(symbol_tables.jump_table.array);
}


  























