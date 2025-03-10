#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "include/data_types.h"
#include "src/code_writer/code_writer.h"
#include "src/hash_table/hash_table.h"
#include "src/parser/parser.h"
#include "src/process_file.h"

bool is_VM_file(char const *str) {
    char *pt = strstr(str, ".vm");
    if (pt != NULL && isupper(*str)) {
        return true;
    }
    return false;
}

void process_dir(FILE *out, struct hash_table *table, char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        char full_path[PATH_MAX];

        // Skip the current and parent directories
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path for the current entry
        snprintf(full_path, PATH_MAX, "%s/%s", path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            process_dir(out, table, full_path);
        } else if (entry->d_type == DT_REG && is_VM_file(entry->d_name)) {
            process_file(out, full_path, table);
        }
    }

    closedir(dir);
}

int main(int argc, char **argv) {
    // initialize the output file
    char *program_name = get_program_name(argv[1]);
    strcat(program_name, ".asm");
    FILE *out = fopen(program_name, "w");

    // write bootstrap code
    write_bootstrap(out);

    // generate the lookup table
    struct hash_table *table = hash_table_command_set_init();

    // determine if input is directory or file
    struct stat st;
    stat(argv[1], &st);

    if (S_ISREG(st.st_mode)) {
        process_file(out, argv[1], table);
    } else if (S_ISDIR(st.st_mode)) {
        process_dir(out, table, argv[1]);
    }

    // write_infinite_loop(out);

    fclose(out);
    hash_table_free(table);
    free(program_name);
}