cmake_minimum_required(VERSION 3.10)

project(HackAssembler C)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/main.c
    src/parser.c
    src/code.c
    src/hashtable.c
    src/symboltable.c
)

add_executable(HackAssembler ${SOURCES})

