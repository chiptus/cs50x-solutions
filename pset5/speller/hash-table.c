#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "linked-list.h"
#include "hash-table.h"
// taken from https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
unsigned int hash_word(const char* word)
 {
     unsigned long hash = 5381;

     for (const char* ptr = word; *ptr != '\0'; ptr++)
     {
         hash = ((hash << 5) + hash) + tolower(*ptr);
     }

     return hash % HASH_TABLE_SIZE;
 }

hash_table* init_table() {
    hash_table* t = (hash_table*)(calloc(1, sizeof(hash_table)));
    t->count=0;
    return t;
}

bool is_word_in_table(const hash_table* t, const char* word) {
    unsigned int hash = hash_word(word);
    if (t->buckets[hash] == NULL) {
        return false;   
    }
    
}

void insert_word(hash_table* t, char* word, int len) {
    unsigned int hash = hash_word(word);
    if (t->buckets[hash] == NULL) {
        t->buckets[hash] = init_list();
    }
    insert_to_top(t->buckets[hash], word);
    t->count++;
}

bool unload_table(hash_table* t) {
    return false;
}