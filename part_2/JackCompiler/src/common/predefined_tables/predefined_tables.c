//
// Created by yousif on 3/14/25.
//

#include "predefined_tables.h"

#include <bits/types/siginfo_t.h>

#define TOKEN_TABLE_SIZE 256
#define KEYWORD_TABLE_SIZE 64
#define OPERATOR_TABLE_SIZE 64

hash_t create_token_table() {
    hash_t table;
    hash_t_init(&table, sizeof(token_t), TOKEN_TABLE_SIZE);

    token_t symbol = T_SYMBOL;
    hash_t_insert(table, new_string("+"), &symbol);
    hash_t_insert(table, new_string("-"), &symbol);
    hash_t_insert(table, new_string("*"), &symbol);
    hash_t_insert(table, new_string("/"), &symbol);
    hash_t_insert(table, new_string("~"), &symbol);
    hash_t_insert(table, new_string("<"), &symbol);
    hash_t_insert(table, new_string(">"), &symbol);
    hash_t_insert(table, new_string("|"), &symbol);
    hash_t_insert(table, new_string("&"), &symbol);
    hash_t_insert(table, new_string("("), &symbol);
    hash_t_insert(table, new_string(")"), &symbol);
    hash_t_insert(table, new_string("{"), &symbol);
    hash_t_insert(table, new_string("}"), &symbol);
    hash_t_insert(table, new_string("["), &symbol);
    hash_t_insert(table, new_string("]"), &symbol);
    hash_t_insert(table, new_string(","), &symbol);
    hash_t_insert(table, new_string("."), &symbol);
    hash_t_insert(table, new_string(";"), &symbol);

    token_t keyword = T_KEYWORD;
    hash_t_insert(table, new_string("class"), &keyword);
    hash_t_insert(table, new_string("method"), &keyword);
    hash_t_insert(table, new_string("function"), &keyword);
    hash_t_insert(table, new_string("return"), &keyword);
    hash_t_insert(table, new_string("if"), &keyword);
    hash_t_insert(table, new_string("this"), &keyword);
    hash_t_insert(table, new_string("else"), &keyword);
    hash_t_insert(table, new_string("while"), &keyword);
    hash_t_insert(table, new_string("do"), &keyword);
    hash_t_insert(table, new_string("int"), &keyword);
    hash_t_insert(table, new_string("char"), &keyword);
    hash_t_insert(table, new_string("boolean"), &keyword);
    hash_t_insert(table, new_string("var"), &keyword);
    hash_t_insert(table, new_string("let"), &keyword);
    hash_t_insert(table, new_string("true"), &keyword);
    hash_t_insert(table, new_string("false"), &keyword);
    hash_t_insert(table, new_string("null"), &keyword);
    hash_t_insert(table, new_string("static"), &keyword);
    hash_t_insert(table, new_string("field"), &keyword);
    hash_t_insert(table, new_string("constructor"), &keyword);
    hash_t_insert(table, new_string("void"), &keyword);

    return table;
}

// create a table with keyword types
hash_t create_keyword_table() {
    hash_t table;
    hash_t_init(&table, sizeof(keyword_t), KEYWORD_TABLE_SIZE);

    keyword_t class = K_CLASS;
    hash_t_insert(table, new_string("class"), &class);

    keyword_t method = K_METHOD;
    hash_t_insert(table, new_string("method"), &method);

    keyword_t function = K_FUNCTION;
    hash_t_insert(table, new_string("function"), &function);

    keyword_t constructor = K_CONSTRUCTOR;
    hash_t_insert(table, new_string("constructor"), &constructor);

    keyword_t int_ = K_INT;
    hash_t_insert(table, new_string("int"), &int_);

    keyword_t char_ = K_CHAR;
    hash_t_insert(table, new_string("char"), &char_);

    keyword_t boolean = K_BOOLEAN;
    hash_t_insert(table, new_string("boolean"), &boolean);

    keyword_t void_ = K_VOID;
    hash_t_insert(table, new_string("void"), &void_);

    keyword_t var = K_VAR;
    hash_t_insert(table, new_string("var"), &var);

    keyword_t static_ = K_STATIC;
    hash_t_insert(table, new_string("static"), &static_);

    keyword_t field = K_FILED;
    hash_t_insert(table, new_string("field"), &field);

    keyword_t let = K_LET;
    hash_t_insert(table, new_string("let"), &let);

    keyword_t do_ = K_DO;
    hash_t_insert(table, new_string("do"), &do_);

    keyword_t while_ = K_WHILE;
    hash_t_insert(table, new_string("while"), &while_);

    keyword_t if_ = K_IF;
    hash_t_insert(table, new_string("if"), &if_);

    keyword_t this_ = K_THIS;
    hash_t_insert(table, new_string("this"), &this_);

    keyword_t else_ = K_ELSE;
    hash_t_insert(table, new_string("else"), &else_);

    keyword_t return_ = K_RETURN;
    hash_t_insert(table, new_string("return"), &return_);

    keyword_t null_ = K_NULL;
    hash_t_insert(table, new_string("null"), &null_);

    keyword_t true_ = K_TRUE;
    hash_t_insert(table, new_string("true"), &true_);

    keyword_t false_ = K_FALSE;
    hash_t_insert(table, new_string("false"), &false_);

    return table;
}

hash_t create_operator_table() {
    hash_t table;
    hash_t_init(&table, sizeof(operator_t), OPERATOR_TABLE_SIZE);

    operator_t bi = BI_OPERATOR;
    hash_t_insert(table, new_string("+"), &bi);
    hash_t_insert(table, new_string("-"), &bi);
    hash_t_insert(table, new_string("*"), &bi);
    hash_t_insert(table, new_string("/"), &bi);
    hash_t_insert(table, new_string("|"), &bi);
    hash_t_insert(table, new_string("&"), &bi);
    hash_t_insert(table, new_string("<"), &bi);
    hash_t_insert(table, new_string(">"), &bi);
    hash_t_insert(table, new_string("="), &bi);

    return table;
}
