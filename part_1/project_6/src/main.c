#include "../include/parser.h"
#include "../include/code.h"
#include "../include/hashtable.h"
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) {
    // open the input file
    FILE *input_file = open_file(argv[1]);

    // declaring the buffer to store the current line
    char buffer[BUFFER_SIZE];

    // generating the tables that contain the symbol to binary mapping
    s_hash_table dest_table = dest_instruction_set();
    s_hash_table comp_table = comp_instruction_set();
    s_hash_table jump_table = jump_instruction_set();

    // fetch line will return null when it reach the end of the file
    while (fetch_line(buffer, BUFFER_SIZE, input_file) != NULL) {

        // advance to the next line if the current line is blank or comment
        while (is_skippable(buffer)) {
            if (advance(buffer, BUFFER_SIZE, input_file) == NULL) {
                return 0;
            }
        }

        // check the type of the instruction
        instruction_t instruction = check_instruction_type(buffer);

        if (instruction == A_INSTRUCTION || instruction == L_INSTRUCTION) {
            // get the numeric value from the instruction
            char *address = symbol(buffer);

            // resolve the value to its binary code
            char *binary_address = decimal_to_binary(address);
            free(address);

            // temp array to hold the full binary instruction
            char binary_instruction[16] = {'0'};

            // concatenate the value's binary to the full instruction
            strcat(binary_instruction, binary_address);
            free(binary_address);

            printf("%s\n", binary_instruction);
        } else {
            // get the the three symbol types from the instruction
            char *dest_symbol = dest(buffer);
            char *comp_symbol = comp(buffer);
            char *jump_symbol = jump(buffer);

            // resolve the symbols to their binary code using the instruction tables
            char *dest_binary = dest_code(dest_symbol, dest_table);
            free(dest_symbol);

            char *comp_binary = comp_code(comp_symbol, comp_table);
            free(comp_symbol);

            char *jump_binary = jump_code(jump_symbol, jump_table);
            free(jump_symbol);

            // temp array to hold the full instruction
            char binary_instruction[16] = {'1', '1', '1'};

            // concatenate the symbols binary to the full instruction
            strcat(binary_instruction, comp_binary);
            strcat(binary_instruction, dest_binary);
            strcat(binary_instruction, jump_binary);

            printf("%s\n", binary_instruction);
        }

    }
    return 0;
}


























