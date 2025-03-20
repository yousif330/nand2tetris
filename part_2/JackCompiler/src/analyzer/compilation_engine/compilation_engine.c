//
// Created by yousif on 3/19/25.
//

#include "compilation_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "../tokenizer/tokenizer.h"
#include "compile_expressions/compile_expressions.h"

static FILE *output_file;

// open the output file
void init_compilation_engine(char const *path) {
    output_file = fopen(path, "w");
    set_output_file(output_file);
}

// compile let statement
void compile_let_statement() {
    print_tag("keyword", "let");

    get_next_token();
    compile_var_name();

    get_next_token();
    process("=");
    print_tag("symbol", "=");

    get_next_token();
    compile_expression();

    get_next_token();
    process(";");
    print_tag("symbol", ";");
}

// free and clean up memory used by the compiler engine
void destruct_compilation_engine() {
    fclose(output_file);
    tokenizer_destruct();
    cleanup_primitive_compilation_engine();
}

int main(int argc, char const *argv[]) {
    atexit(destruct_compilation_engine);

    tokenizer_init(argv[1]);
    init_compilation_engine("out.XML");

    Token c = get_next_token();
    compile_let_statement();

    return 0;
}