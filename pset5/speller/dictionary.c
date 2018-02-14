#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"
#include "hash-table.h"

hash_table* table = NULL;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word) {
    if (table == NULL) {
        return false;
    }
    return is_word_in_table(table, word);
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
            insert_word(table, word, word_len);
            word_len = 0;
            continue;
        }
        word[word_len] = c;
        word_len++;
    }
    
    fclose(dictionary_file);
    
    return true;
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