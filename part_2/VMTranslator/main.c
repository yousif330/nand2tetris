#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/code_writer/code_writer.h"
#include "src/hash_table/hash_table.h"
#include "src/parser/parser.h"

#define BUFFER_SIZE 1024
#define COMMAND_BUFFER_SIZE 16

int main(int argc, char **argv) {
    // buffer to store lines
    char buffer[BUFFER_SIZE];

    char *program_name = get_program_name(argv[1]);

    struct hash_table *table = hash_table_command_set_init();

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(strcat(program_name, "asm"), "w");

    while (fgets(buffer, BUFFER_SIZE, input_file)) {
        // buffer to store commands
        char command_buffer[COMMAND_BUFFER_SIZE];

        remove_comment(buffer);

        while (is_string_blank(buffer)) {
            if (!fgets(buffer, BUFFER_SIZE, input_file)) {
                hash_table_free(table);
                return 0;
            }
            remove_comment(buffer);
        }

        trim_string(buffer);

        get_command(command_buffer, buffer);
        enum command_type command = get_command_type(table, command_buffer);

        if (command == C_PUSH || command == C_POP) {
            get_arg1(command_buffer, buffer);
            char *arg1 = get_mem_segment(table, command_buffer);
            int arg2 = get_arg2(buffer);

            // if the first argument is static, provide the program name to the
            // code writer
            // refactor this into its own function later
            if (*arg1 == 'S') {
                char number[64];
                sprintf(number, "%d", arg2);

                arg1 = program_name;
                strcpy(strchr(arg1, '.') + 1, number);
            }

            write_push_pop(arg1, arg2, command, output_file);
        } else if (command == C_ARITHMETIC) {
            char op = get_operation(table, command_buffer);
            write_arithmetic(op, output_file);
        }
    }

    free(program_name);
    fclose(input_file);
    fclose(output_file);
    hash_table_free(table);

    return 0;
}
