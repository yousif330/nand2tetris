//
// Created by yousif on 3/2/25.
//

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "../../include/data_types.h"

struct hash_table *hash_table_command_set_init();

struct hash_table *hash_table_search(struct hash_table *table, const char *key);

void hash_table_free(struct hash_table *table);

void hash_table_insert(struct hash_table *table, char *key, char *value,
                       enum command_type command);

#endif  // HASH_TABLE_H
