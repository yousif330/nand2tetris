//
// Created by yousif on 3/2/25.
//

#include "code_writer.h"

#include <stdlib.h>
#include <string.h>

void write_push(char *arg1, int arg2, FILE *out) {
    fprintf(out, "// push %s %d\n", arg1, arg2);
    fprintf(out, "@%s\nD=A\n@%d\n", arg1, arg2);
    fprintf(out, "A=D+A\nD=M\n");
    fprintf(out, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
}

void write_pop(char *arg1, int arg2, FILE *out) {
    fprintf(out, "// pop %s %d\n", arg1, arg2);
    fprintf(out, "@SP\nAM=M-1\nD=M\n@R0\nM=D\n");
    fprintf(out, "@%s\nD=M\n@%d\nD=D+A\n@R1\nM=D\n", arg1, arg2);
    fprintf(out, "@R0\nD=M\n@R1\nA=M\nM=D\n");
}

void write_constant_push(int arg2, FILE *out) {
    fprintf(out, "// push constant %d\n", arg2);
    fprintf(out, "@%d\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", arg2);
}

void write_push_pop(char *arg1, int arg2, enum command_type command,
                    FILE *out) {
    if (strcmp(arg1, "C") == 0) {
        write_constant_push(arg2, out);
    } else if (command == C_PUSH) {
        write_push(arg1, arg2, out);
    } else if (command == C_POP) {
        write_pop(arg1, arg2, out);
    }
}

void write_uni_operation(char op, FILE *out) {
    fprintf(out, "@SP\nAM=M-1\n");
    if (op == 'n') {
        fprintf(out, "M=-M\n");
    } else {
        fprintf(out, "M=!M\n");
    }
    fprintf(out, "@SP\nM=M+1\n");
}

void write_bi_operation(char op, FILE *out) {
    fprintf(out, "@SP\nAM=M-1\nD=M\n");
    fprintf(out, "@SP\nAM=M-1\n");

    fprintf(out, "D=D%cM\n", op);

    fprintf(out, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
}

void write_arithmetic(char op, FILE *out) {
    switch (op) {
        case '!':
        case 'n':
            write_uni_operation(op, out);
            break;
        case '+':
        case '-':
        case '&':
        case '|':
            write_bi_operation(op, out);
            break;
        default:
            exit(EXIT_FAILURE);
    }
}
