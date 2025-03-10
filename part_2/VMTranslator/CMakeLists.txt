cmake_minimum_required(VERSION 3.30)
project(VMTranslator C)

set(CMAKE_C_STANDARD 11)

add_executable(VMTranslator main.c
        src/parser/parser.c
        src/parser/parser.h
        include/data_types.h
        src/hash_table/hash_table.c
        src/hash_table/hash_table.h
        src/code_writer/code_writer.c
        src/code_writer/code_writer.h
        src/process_file.c
        src/process_file.h)
