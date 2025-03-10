//
// Created by yousif on 3/2/25.
//

#include "code_writer.h"

#include <stdlib.h>

// write the assembly for push operations
void write_push(char *arg1, int arg2, FILE *out) {
    fprintf(out, "@%s\nD=M\n@%d\n", arg1, arg2);
    fprintf(out, "A=D+A\nD=M\n");
    fprintf(out, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
}

// write the assembly for pop operations
void write_pop(char *arg1, int arg2, FILE *out) {
    fprintf(out, "@SP\nAM=M-1\nD=M\n@R13\nM=D\n");
    fprintf(out, "@%s\nD=M\n@%d\nD=D+A\n@R14\nM=D\n", arg1, arg2);
    fprintf(out, "@R13\nD=M\n@R14\nA=M\nM=D\n");
}

// write assembly for pointer pop
void write_pointer_pop(int arg2, FILE *out) {
    if (arg2 == 0) {
        fprintf(out, "@SP\nAM=M-1\nD=M\n@THIS\nM=D\n");
    } else {
        fprintf(out, "@SP\nAM=M-1\nD=M\n@THAT\nM=D\n");
    }
}

// write assembly for pointer push
void write_pointer_push(int arg2, FILE *out) {
    if (arg2 == 0) {
        fprintf(out, "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    } else {
        fprintf(out, "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    }
}

// write the assembly for temp push
void write_temp_push(int arg2, FILE *out) {
    fprintf(out, "@R%d\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", arg2 + 5);
}

// write the assembly for temp pop
void write_temp_pop(int arg2, FILE *out) {
    fprintf(out, "@SP\nAM=M-1\nD=M\n@R%d\nM=D\n", arg2 + 5);
}

// write the assembly for push constants operations
void write_constant_push(int arg2, FILE *out) {
    fprintf(out, "@%d\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", arg2);
}

// write the assembly for static push
void write_static_push(char *arg1, int arg2, FILE *out) {
    fprintf(out, "@%s.%d\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n", arg1, arg2);
}

// write the assembly for static pop
void write_static_pop(char *arg1, int arg2, FILE *out) {
    fprintf(out, "@SP\nAM=M-1\nD=M\n@%s.%d\nM=D\n", arg1, arg2);
}

void write_static_push_pop(char *arg1, int arg2, FILE *out,
                           enum command_type command) {
    if (command == C_PUSH) {
        write_static_push(arg1, arg2, out);
    } else if (command == C_POP) {
        write_static_pop(arg1, arg2, out);
    }
}

void write_push_pop(char *arg1, int arg2, enum command_type command,
                    FILE *out) {
    // if arg1 is "T" then the command involve temp
    if (*arg1 == 'P') {
        if (command == C_PUSH) {
            write_pointer_push(arg2, out);
        } else {
            write_pointer_pop(arg2, out);
        }
    } else if (*arg1 == 't') {
        if (command == C_PUSH) {
            write_temp_push(arg2, out);
        } else {
            write_temp_pop(arg2, out);
        }
    }
    // if arg1 is "C" then the command involve constants
    else if (*arg1 == 'C') {
        write_constant_push(arg2, out);
    } else if (command == C_PUSH) {
        write_push(arg1, arg2, out);
    } else if (command == C_POP) {
        write_pop(arg1, arg2, out);
    }
}

// write the assembly for single operand arithmetic operations
void write_uni_operation(char op, FILE *out) {
    fprintf(out, "@SP\nAM=M-1\n");
    if (op == 'n') {
        fprintf(out, "M=-M\n");
    } else {
        fprintf(out, "M=!M\n");
    }
    fprintf(out, "@SP\nM=M+1\n");
}

// write the assembly for two operands arithmetic operations
void write_bi_operation(char op, FILE *out) {
    fprintf(out, "@SP\nAM=M-1\nD=M\n");
    fprintf(out, "@SP\nAM=M-1\n");

    if (op == '-') {
        fprintf(out, "D=M-D\n");
    } else {
        fprintf(out, "D=D%cM\n", op);
    }

    fprintf(out, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
}

// write the assembly for comparison operations
void write_comparisons_operation(char op, FILE *out, char *program_name) {
    static int count = 0;
    fprintf(out, "@SP\nAM=M-1\nD=M\n@SP\nAM=M-1\nD=M-D\n@TRUE.%s.%d\n",
            program_name, count);

    if (op == 'e') {
        fprintf(out, "D;JEQ\n");
    } else if (op == 'g') {
        fprintf(out, "D;JGT\n");
    } else {
        fprintf(out, "D;JLT\n");
    }
    fprintf(out, "@SP\nA=M\nM=0\n@SP\nM=M+1\n@END.%s.%d\n0;JMP\n", program_name,
            count);
    fprintf(out, "(TRUE.%s.%d)\n@SP\nA=M\nM=-1\n@SP\nM=M+1\n(END.%s.%d)\n",
            program_name, count, program_name, count);

    count++;
}

void write_arithmetic(char op, FILE *out, char *current_function) {
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
        case 'e':
        case 'g':
        case 'l':
            write_comparisons_operation(op, out, current_function);
            break;
        default:
            exit(EXIT_FAILURE);
    }
}

void write_infinite_loop(FILE *out) { fprintf(out, "(END)\n@END\n0;JMP\n"); }

// write the assembly for declaring a function
void write_function(FILE *out, char *arg1, int arg2) {
    fprintf(out, "(%s)\n", arg1);

    for (int i = 0; i < arg2; i++) {
        write_constant_push(0, out);
    }
}

// write the assembly for declaring a label
void write_label(FILE *out, char *arg1, char *current_function) {
    fprintf(out, "(%s$%s)\n", current_function, arg1);
}

// write assembly for if-goto commands
void write_if(FILE *out, char *arg1, char *current_function) {
    fprintf(out, "@SP\nAM=M-1\nD=M\n");
    fprintf(out, "@%s$%s\nD;JNE\n", current_function, arg1);
}

// write assembly for goto commands
void write_goto(FILE *out, char *arg1, char *current_function) {
    fprintf(out, "@%s$%s\n0;JMP\n", current_function, arg1);
}

// write assembly for call command
void write_call(FILE *out, char *arg1, int arg2, char *current_function,
                int call_count) {
    // push return address
    fprintf(out, "@%s$ret.%d\nD=A\n", current_function, call_count);
    fprintf(out, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    // push LCL
    fprintf(out, "@LCL\nD=M\n");
    fprintf(out, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    // push ARG
    fprintf(out, "@ARG\nD=M\n");
    fprintf(out, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    // push THIS
    fprintf(out, "@THIS\nD=M\n");
    fprintf(out, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");
    // push THAT
    fprintf(out, "@THAT\nD=M\n");
    fprintf(out, "@SP\nA=M\nM=D\n@SP\nM=M+1\n");

    // ARG = SP - 5 - arg2
    // LCL = SP
    fprintf(out, "@SP\nD=M\n@5\nD=D-A\n");
    fprintf(out, "@%d\nD=D-A\n@ARG\nM=D\n", arg2);
    fprintf(out, "@SP\nD=M\n@LCL\nM=D\n");

    // goto f
    fprintf(out, "@%s\n0;JMP\n", arg1);
    fprintf(out, "(%s$ret.%d)\n", current_function, call_count);
}

// write the assembly for return command
void write_return(FILE *out) {
    // TEMP 0 = retAddress
    fprintf(out, "@LCL\nD=M\n@5\nA=D-A\nD=M\n@R13\nM=D\n");
    // ARG = pop()
    fprintf(out, "@SP\nAM=M-1\nD=M\n@ARG\nA=M\nM=D\n");
    // SP = ARG + 1
    fprintf(out, "@ARG\nD=M+1\n@SP\nM=D\n");

    // restore mem segments
    fprintf(out, "@LCL\nAM=M-1\nD=M\n@THAT\nM=D\n");
    fprintf(out, "@LCL\nAM=M-1\nD=M\n@THIS\nM=D\n");
    fprintf(out, "@LCL\nAM=M-1\nD=M\n@ARG\nM=D\n");
    fprintf(out, "@LCL\nAM=M-1\nD=M\n@LCL\nM=D\n");

    // goto retAddress
    fprintf(out, "@R13\nA=M\n0;JMP\n");
}

void write_bootstrap(FILE *out) {
    fprintf(out, "@256\nD=A\n@SP\nM=D\n");
    fprintf(out, "@Sys.init\n0;JMP\n");
}
