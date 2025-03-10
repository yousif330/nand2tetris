//
// Created by yousif on 3/8/25.
//

#ifndef PROCESS_FILE_H
#define PROCESS_FILE_H

#include <stdio.h>

#include "../include/data_types.h"

void process_file(FILE *out, const char *path, struct hash_table *table);

#endif  // PROCESS_FILE_H
