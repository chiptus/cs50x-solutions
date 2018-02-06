#include <stdbool.h>

#include "linked-list.h"

const int HASH_TABLE_SIZE = 10^5;

typedef struct hash_table {
    list slots[HASH_TABLE_SIZE];
    int count;
} hash_table;

hash_table* init_table();

bool is_word_in_table(const hash_table* t, const char* word);

void insert_word(hash_table* t, char* word, int len);

bool unload_table(hash_table* t);
