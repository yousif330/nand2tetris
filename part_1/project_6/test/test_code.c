#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/code.h"

void test_dtob() {
    char *got = decimal_to_binary("12");
    char *want = "000000000001100";

    if (strcmp(got, want)) {
        printf("test_dtob: failed\nexpected: %s\ngot: %s\n", want, got);
    } else {
        puts("test_dtob: successful");
    }

    free(got);
}


void test_dest_code() {
    char *got = dest_code("DM");
    char *want = "011";

    if (strcmp(got, want)) {
        printf("test_dest_code: failed\nexpected: %s\ngot: %s\n", want, got);
    } else {
        puts("test_dest_code: successful");
    }

    free(got);
}


int main() {
    test_dtob();
    test_dest_code();
    return 0;
}



