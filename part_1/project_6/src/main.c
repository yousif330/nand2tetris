#include <stdlib.h>
#include <string.h>

#include "../include/code.h"
#include "../include/parser.h"
#include "../include/symboltable.h"
#include "../include/hashtable.h"

#define BUFFER_SIZE 1024

// a struct to group all the input output files data
typedef struct file_context {
    FILE *input_file;
    FILE *output_file;
    char *buffer;
} file_context;

s_table_int *preprocess_file(FILE *input_file, char buffer[]);
void handle_a_instruction(file_context ctx, s_table_int *table);
void handle_c_instruction(file_context ctx, s_predefined_symbols symbol_tables);

int main(int argc, char **argv) {
    file_context ctx;
    // open the input file
    ctx.input_file = open_file(argv[1]);

    // open the output file
    ctx.output_file = open_output_file(argv[1]);

    // declaring the buffer to store the current line
    char buffer[BUFFER_SIZE];
    ctx.buffer = buffer;

    s_table_int *table = preprocess_file(ctx.input_file, buffer);

    rewind(ctx.input_file);

    int address_count = 16;

    // generating the tables that contain the symbol to binary mapping
    s_predefined_symbols symbol_tables = build_symbol_tables();

    // fetch line will return null when it reach the end of the file
    while (fetch_line(buffer, BUFFER_SIZE, ctx.input_file) != NULL) {
        // advance to the next line if the current line is blank or comment
        while (is_skippable(buffer)) {
            if (advance(buffer, BUFFER_SIZE, ctx.input_file) == NULL) {
                return 0;
            }
        }

        // check the type of the instruction
        instruction_t instruction = check_instruction_type(buffer);

        if (instruction == A_INSTRUCTION) {
            handle_a_instruction(ctx, table);
        } else if (instruction == C_INSTRUCTION) {
            handle_c_instruction(ctx, symbol_tables);
        }
    }

    fclose(ctx.output_file);
    fclose(ctx.input_file);

    // free hash table
    delete_hash_table(table);

    // free symbolic tables
    delete_symbol_tables(symbol_tables);

    return 0;
}

void handle_a_instruction(file_context ctx, s_table_int *table) {
    // count the used memory addresses
    static int address_count = 16;

    // get the numeric value from the instruction
    char *address = symbol(ctx.buffer);

    char *binary_address;

    if (is_numeric(address)) {
        binary_address = decimal_to_binary(address);
        free(address);
    } else {
        s_table_int *p = search_table(table, address);

        if (p == NULL) {
            insert_at_table(table, address, address_count);
            binary_address = int_to_binary(address_count++);
        } else {
            binary_address = int_to_binary(p->address);
            free(address);
        }
    }

    // temp array to hold the full binary instruction
    char binary_instruction[16] = {'0'};

    // concatenate the value's binary to the full instruction
    strcat(binary_instruction, binary_address);
    free(binary_address);

    fprintf(ctx.output_file, "%s\n", binary_instruction);
}

void handle_c_instruction(file_context ctx, s_predefined_symbols symbol_tables) {
    // get the the three symbol types from the instruction
    char *dest_symbol = dest(ctx.buffer);
    char *comp_symbol = comp(ctx.buffer);
    char *jump_symbol = jump(ctx.buffer);

    // resolve the symbols to their binary code using the instruction
    // tables
    char *dest_binary = dest_code(dest_symbol, symbol_tables.dest_table);
    free(dest_symbol);

    char *comp_binary = comp_code(comp_symbol, symbol_tables.comp_table);
    free(comp_symbol);

    char *jump_binary = jump_code(jump_symbol, symbol_tables.jump_table);
    free(jump_symbol);

    // temp array to hold the full instruction
    char binary_instruction[16] = {'1', '1', '1'};

    // concatenate the symbols binary to the full instruction
    strcat(binary_instruction, comp_binary);
    strcat(binary_instruction, dest_binary);
    strcat(binary_instruction, jump_binary);

    fprintf(ctx.output_file, "%s\n", binary_instruction);
}

// function to parse the file a generate a hash table for all labels
s_table_int *preprocess_file(FILE *input_file, char buffer[]) {
    // count the line number
    int line_number_count = 0;

    s_table_int *table = create_table_with_predefined_symbols();

    while (fetch_line(buffer, BUFFER_SIZE, input_file) != NULL) {
        // advance to the next line if the current line is blank or comment
        while (is_skippable(buffer)) {
            if (advance(buffer, BUFFER_SIZE, input_file) == NULL) {
                return 0;
            }
        }

        // check the type of the instruction
        instruction_t instruction = check_instruction_type(buffer);

        if (instruction == L_INSTRUCTION) {
            char *label = symbol(buffer);

            if (search_table(table, label) == NULL) {
                insert_at_table(table, label, line_number_count);
            } else {
                free(label);
            }
        } else {
            line_number_count++;
        }

    }
    return table;
}
                 
























