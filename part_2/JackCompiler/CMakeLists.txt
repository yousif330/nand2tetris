cmake_minimum_required(VERSION 3.30)
project(JackCompiler C)

set(CMAKE_C_STANDARD 11)

add_executable(JackCompiler main.c
        src/common/hash_table/hash_table.c
        src/common/hash_table/hash_table.h
        src/common/data_types.h
        src/analyzer/tokenizer/tokenizer.c
        src/analyzer/tokenizer/tokenizer.h
        src/common/predefined_tables/predefined_tables.c
        src/common/predefined_tables/predefined_tables.h
        src/analyzer/compilation_engine/compilation_engine.c
        src/analyzer/compilation_engine/compilation_engine.h
        src/analyzer/compilation_engine/compile_expressions/compile_expressions.c
        src/analyzer/compilation_engine/compile_expressions/compile_expressions.h
)
