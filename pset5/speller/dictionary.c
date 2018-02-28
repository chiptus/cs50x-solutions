#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"
#include "hash-table.h"

hash_table* table = NULL;

char* copy_as_lower_case(const char* word, int len);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word) {
    if (table == NULL) {
        return false;
    }
    char* lower_word = copy_as_lower_case(word, strlen(word));
    bool ans = is_word_in_table(table, lower_word);
    free(lower_word);
    return ans;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary) {
    table = init_table();
    
    FILE* dictionary_file = fopen(dictionary, "r");
    
    if (dictionary_file == NULL) {
        return false;
    }
    
    char word[LENGTH];
    char c;
    int word_len = 0;
    while ((c = fgetc(dictionary_file)) != EOF) {
        if (c == '\n') { //end of line is end of word
            word[word_len] = 0;
            insert_word(table, copy_as_lower_case(word, word_len), word_len);
            word_len = 0;
            continue;
        }
        word[word_len] = c;
        word_len++;
    }
    fclose(dictionary_file);
    // print_dict();
    return true;
}

char* copy_as_lower_case(const char* word, int len) {
    char* new_word = malloc(sizeof(char) * len + 1);
    for (int i=0; i<len; i++) {
        new_word[i] = tolower(word[i]);
    }
    new_word[len] = 0;
    return new_word;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void) {
    if (table == NULL) {
        return 0;
    }
    return table->count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void) {
    if (table == NULL) {
        return true;
    }
    bool unloaded = unload_table(table);
    table = NULL;
    return unloaded;
}

void print_dict() {
    for (int i=0; i<HASH_TABLE_SIZE; i++) {
        printf("%i:\n", i);
        print_list(table->buckets[i]);
    }
}