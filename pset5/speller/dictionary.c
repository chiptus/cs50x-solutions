/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"
#include "trie.h"

trie* dict = NULL;
int count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    if (dict == NULL) {
        return false;
    }
    return is_word_in_trie(dict, word);
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    dict = init_trie();
    
    FILE* dictionary_file = fopen(dictionary, "r");
    
    if (dictionary_file == NULL) {
        return false;
    }
    char word[LENGTH];
    char tempChar;
    int i = 0;
    while ((tempChar = fgetc(dictionary_file)) != EOF) {
        // if (i > LENGTH) {
        //     skip_line(dictionary_file);
        //     continue;
        // }
        if (tempChar  == '\n') {
            word[i] = '\0';
            insert_word(dict,word);
            i = 0;
            count++;
            continue;
        }
        word[i] = tempChar;
        i++;
    }
    
    free(dictionary_file);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dict == NULL) {
        return 0;
    }
    return count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    count = 0;
    bool unloaded = unload_trie(dict);
    if (unloaded) {
        dict = NULL;
    }
    return unloaded;
}
