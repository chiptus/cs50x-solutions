#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "trie.h"

bool unload_node_array(trie_node** node_array);

trie* init_trie() {
    trie* t = (trie *)malloc(sizeof(struct trie));
    for (int i=0; i<27;i++) {
        t->head[i] = NULL;
    }
    return t;
}

int get_char_index(char c) {
    int i = (int)c;
    if (isupper(c)) {
        return i-65;
    }
    if (islower(c)) {
        return i-97;
    }
    // c is '
    return 26;
}

bool is_char_valid(char c) {
    return isalpha(c) || c == '\'';
}

// int main() {
//     trie* trie = malloc(sizeof(struct trie)) ;
//     bool answer = is_word_in_trie(trie, "walla");
//     printf("trie should be empty: %s\n", !answer ? "suc" : "fail");
//     insert_word(trie, "newword");
//     bool new_word_in = is_word_in_trie(trie, "newword");
//     printf("trie should have newword: %s\n", new_word_in ? "suc" : "fail");
//     return 0;
// }


bool is_word_in_trie(const trie* trie, const char* word) {
    trie_node* current = trie->head[get_char_index(word[0])];
    if (current == NULL) {
        return false;
    }
    int i = 1;
    int len = strlen(word);
    // walk on the trie nodes following the word characters
    while (i < len && current != NULL) {
        current = current->next[get_char_index(word[i])];
        i++;
    }
    if (i == len && current != NULL) {
        return current->end;
    }
    return false;
}

trie_node* init_node() {
    trie_node* n = (trie_node*)malloc(sizeof(trie_node));
    for (int i=0; i<27; i++) {
        n->next[i] = NULL;
    }
    n->end=false;
    return n;
}

void insert_word(trie* trie, char* word) {
    int len = strlen(word);
    if (trie->head[get_char_index(word[0])] == NULL) {
        trie->head[get_char_index(word[0])] = init_node();
    }
    trie_node* current_node = trie->head[get_char_index(word[0])];
    for (int i = 1; i < len; i++) {
        
        int char_index = get_char_index(word[i]);
        if (current_node->next[char_index] == NULL) {
            current_node->next[char_index] = init_node();
        }
        current_node = current_node->next[char_index];
    }
    current_node->end = true;
}

bool unload_trie(trie* t) {
    bool unloaded = unload_node_array(t->head);
    if (unloaded) {
        free(t);
    }
    return unloaded;
}

bool unload_node_array(trie_node* node_array[]) {
    bool unloaded = true;
    for (int i=0; i<27 && unloaded; i++) {
        trie_node* current = node_array[i];
        if (current == NULL) {
            continue;
        }
        unloaded = unloaded && unload_node_array(current->next);
        if (unloaded) {
            free(current);
        }
    }
    return unloaded;
}