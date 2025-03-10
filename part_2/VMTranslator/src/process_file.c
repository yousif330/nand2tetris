//
// Created by yousif on 3/8/25.
//

#include "process_file.h"

#include <stdlib.h>
#include <string.h>

#include "code_writer/code_writer.h"
#include "parser/parser.h"

#define BUFFER_SIZE 1024
#define TEMP_BUFFER_SIZE 16
#define LABEL_BUFFER_SIZE 1024

struct file_context initialize_file_context(char const *path);
void clean_up(struct file_context ctx);
void handle_push_pop_command(struct file_context ctx, FILE *out,
                             enum command_type command,
                             struct hash_table *table);
int process_line(struct file_context ctx);
void handle_function_command(struct file_context ctx, FILE *out,
                             char *current_function);
void handle_label_command(struct file_context ctx, FILE *out,
                          char *current_function);
void handle_if_command(struct file_context ctx, FILE *out,
                       char *current_function);
void handle_goto_command(struct file_context ctx, FILE *out,
                         char *current_function);
void handle_call_command(struct file_context ctx, FILE *out,
                         char *current_function, int call_count);

void process_file(FILE *out, const char *path, struct hash_table *table) {
    // buffer to store lines
    char buffer[BUFFER_SIZE];

    // initialize input/out files
    struct file_context ctx = initialize_file_context(path);
    ctx.buffer = buffer;

    int call_count = 0;

    // buffer to store the current function
    char current_function[BUFFER_SIZE];
    current_function[0] = '\0';

    while (fgets(buffer, BUFFER_SIZE, ctx.in)) {
        // buffer to store commands
        char temp_buffer[TEMP_BUFFER_SIZE];

        // process line to be ready for being split into its components
        if (process_line(ctx) == 0) {
            return;
        }

        // store the command in the temp buffer
        get_command(temp_buffer, buffer);
        // get the command type
        enum command_type command = get_command_type(table, temp_buffer);

        if (command == C_PUSH || command == C_POP) {
            handle_push_pop_command(ctx, out, command, table);
        } else if (command == C_ARITHMETIC) {
            char op = get_operation(table, temp_buffer);
            write_arithmetic(op, out, current_function);
        } else if (command == C_FUNCTION) {
            handle_function_command(ctx, out, current_function);
            call_count = 0;
        } else if (command == C_LABEL) {
            handle_label_command(ctx, out, current_function);
        } else if (command == C_IF) {
            handle_if_command(ctx, out, current_function);
        } else if (command == C_GOTO) {
            handle_goto_command(ctx, out, current_function);
        } else if (command == C_CALL) {
            handle_call_command(ctx, out, current_function, call_count);
            call_count++;
        } else if (command == C_RETURN) {
            write_return(out);
        }
    }

    clean_up(ctx);
}

// a function to initialize the input/output file context
struct file_context initialize_file_context(char const *path) {
    struct file_context ctx;
    ctx.in = fopen(path, "r");
    ctx.file_name = get_file_name(path);

    ctx.buffer = NULL;

    return ctx;
}

// a function to process lines (remove comments, skip blanks, trimming)
int process_line(struct file_context ctx) {
    remove_comment(ctx.buffer);

    while (is_string_blank(ctx.buffer)) {
        if (!fgets(ctx.buffer, BUFFER_SIZE, ctx.in)) {
            clean_up(ctx);
            return 0;
        }
        remove_comment(ctx.buffer);
    }

    trim_string(ctx.buffer);
    return 1;
}

// a function to handle push/pop commands
void handle_push_pop_command(struct file_context ctx, FILE *out,
                             enum command_type command,
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
        arg1 = ctx.file_name;
        // special function to handle static variables
        write_static_push_pop(arg1, arg2, out, command);
    } else {
        // otherwise use generic function
        write_push_pop(arg1, arg2, command, out);
    }
}

// a function to handle function commands
void handle_function_command(struct file_context ctx, FILE *out,
                             char *current_function) {
    // a temp buffer to store the first argument of the command
    get_arg1(current_function, ctx.buffer);
    int arg2 = get_arg2(ctx.buffer);

    write_function(out, current_function, arg2);
}

// a function to handle label commands
void handle_label_command(struct file_context ctx, FILE *out,
                          char *current_function) {
    char temp_buffer[LABEL_BUFFER_SIZE];
    get_arg1(temp_buffer, ctx.buffer);

    write_label(out, temp_buffer, current_function);
}

// a function to handle if-goto commands
void handle_if_command(struct file_context ctx, FILE *out,
                       char *current_function) {
    char temp_buffer[LABEL_BUFFER_SIZE];
    get_arg1(temp_buffer, ctx.buffer);

    write_if(out, temp_buffer, current_function);
}

// a function to handle goto commands
void handle_goto_command(struct file_context ctx, FILE *out,
                         char *current_function) {
    char temp_buffer[LABEL_BUFFER_SIZE];
    get_arg1(temp_buffer, ctx.buffer);

    write_goto(out, temp_buffer, current_function);
}

// a function to handle call command
void handle_call_command(struct file_context ctx, FILE *out,
                         char *current_function, int call_count) {
    char temp_buffer[LABEL_BUFFER_SIZE];
    get_arg1(temp_buffer, ctx.buffer);
    int arg2 = get_arg2(ctx.buffer);

    write_call(out, temp_buffer, arg2, current_function, call_count);
}

// a function to cleaning up the heap and closing the files
void clean_up(struct file_context ctx) {
    free(ctx.file_name);
    fclose(ctx.in);
}
