#include <stdio.h>
#include <stdbool.h>
#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void test_symbol() {
    char *got = symbol("(LOOP)");
    char *want = "LOOP";

    if (strcmp(got, want)) {
        printf("test_symbol: failed\nexpected: %s\ngot: %s\n", want, got);
    } else {
        puts("test_symbol: successful");
    }
    printf("\n");
    free(got);
}


void test_dest() {
    char *got = dest("M+1;JGT");
    char *want = "";

    if (strcmp(got, want)) {
        printf("test_dest: failed\nexpected: %s\ngot: %s\n", want, got);
    } else {
        puts("test_dest: successful");
    }
    printf("\n");
    free(got);
}


void test_jump() {
    char *got = jump("DM=M+1");
    char *want = "";

    if (strcmp(got, want)) {
        printf("test_jump: failed\nexpected: %s\ngot: %s\n", want, got);
    } else {
        puts("test_jump: successful");
    }
    printf("\n");
    free(got);
}


void test_comp() {
    char *got = comp("DM=M+1;JGT");
    char *want = "M+1";

    if (strcmp(got, want)) {
        printf("test_comp: failed\nexpected: %s\ngot: %s\n", want, got);
    } else {
        puts("test_comp: successful");
    }
    printf("\n");
    free(got);
}
        

int main() {
    test_symbol();
    test_dest();
    test_jump();
    test_comp();
    return 0;
}

