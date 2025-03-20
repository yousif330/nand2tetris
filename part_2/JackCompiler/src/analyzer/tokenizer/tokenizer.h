//
// Created by yousif on 3/14/25.
//

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "../../common/data_types.h"

void tokenizer_init(const char *path);

Token get_current_token();

void unget_token(Token t);

Token get_next_token();

Token look_ahead();

void tokenizer_destruct();

void set_current_token(Token token);

#endif  // TOKENIZER_H
