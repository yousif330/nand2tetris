#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/code_writer/code_writer.h"
#include "src/hash_table/hash_table.h"
#include "src/parser/parser.h"

#define BUFFER_SIZE 1024
#define COMMAND_BUFFER_SIZE 16
#define TEMP_BUFFER_SIZE 16

struct file_context {
    FILE *in;
    FILE *out;
    char *program_name;
    char *buffer;
};

struct file_context initialize_file_context(char *path);
void clean_up(struct file_context ctx, struct hash_table *table);
void handle_push_pop_command(struct file_context ctx, enum command_type command,
                             struct hash_table *table);
void process_line(struct file_context ctx, struct hash_table *table);

int main(int argc, char **argv) {
    // buffer to store lines
    char buffer[BUFFER_SIZE];
    // initialize a hash table with predefined symbols
    struct hash_table *table = hash_table_command_set_init();

    // initialize input/out files
    struct file_context ctx = initialize_file_context(argv[1]);
    ctx.buffer = buffer;

    while (fgets(buffer, BUFFER_SIZE, ctx.in)) {
        // buffer to store commands
        char temp_buffer[TEMP_BUFFER_SIZE];

        // process line to be ready for being split into its components
        process_line(ctx, table);

        // store the command in the temp buffer
        get_command(temp_buffer, buffer);
        // get the command type
        enum command_type command = get_command_type(table, temp_buffer);

        if (command == C_PUSH || command == C_POP) {
            handle_push_pop_command(ctx, command, table);
        } else if (command == C_ARITHMETIC) {
            char op = get_operation(table, temp_buffer);
            write_arithmetic(op, ctx.out, ctx.program_name);
        }
    }

    write_infinite_loop(ctx.out);
    clean_up(ctx, table);

    return 0;
}

// a function to initialize the input/output file context
struct file_context initialize_file_context(char *path) {
    struct file_context ctx;
    ctx.in = fopen(path, "r");
    ctx.program_name = get_program_name(path);
    ctx.out = fopen(strcat(ctx.program_name, ".asm"), "r");

    char *name_extension = strrchr(ctx.program_name, '.');
    name_extension[0] = '\0';

    ctx.buffer = NULL;

    return ctx;
}

// a function to process lines (remove comments, skip blanks, trimming)
void process_line(struct file_context ctx, struct hash_table *table) {
    remove_comment(ctx.buffer);

    while (is_string_blank(ctx.buffer)) {
        if (!fgets(ctx.buffer, BUFFER_SIZE, ctx.in)) {
            clean_up(ctx, table);
            return;
        }
        remove_comment(ctx.buffer);
    }

    trim_string(ctx.buffer);
}

// a function to handle push/pop commands
void handle_push_pop_command(struct file_context ctx, enum command_type command,
                             struct hash_table *table) {
    // a temp buffer to store the first argument of the command
    char temp_buffer[TEMP_BUFFER_SIZE];
    get_arg1(temp_buffer, ctx.buffer);

    // using the hash-table to get the symbol for the first argument
    char *arg1 = get_mem_segment(table, temp_buffer);
    int arg2 = get_arg2(ctx.buffer);

    // if the symbol is 'S' then the mem-segment is for static variables
    if (*arg1 == 'S') {
        // the first argument will be the program name
        arg1 = ctx.program_name;
        // special function to handle static vatiables
        write_static_push_pop(arg1, arg2, ctx.out, command);
    } else {
        // otherwise use generic function
        write_push_pop(arg1, arg2, command, ctx.out);
    }
}

// a function to cleaning up the heap and closing the files
void clean_up(struct file_context ctx, struct hash_table *table) {
    free(ctx.program_name);
    fclose(ctx.in);
    fclose(ctx.out);
    hash_table_free(table);
}
