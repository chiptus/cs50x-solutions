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
    dict = init_trie();
    
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
            insert_word(dict, word, word_len);
            word_len = 0;
            count++;
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
    bool unloaded = unload_trie(dict);
    if (unloaded) {
        count = 0;
        dict = NULL;
    }
    return unloaded;
}
