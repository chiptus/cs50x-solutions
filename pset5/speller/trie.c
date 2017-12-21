#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "trie.h"

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


bool is_word_in_trie(const trie* trie, char* word) {
    if (trie->head == NULL) {
        return false;
    }
    trie_node* current = trie->head[get_char_index(word[0])];
    if (current == NULL) {
        return false;
    }
    int i = 1;
    int len = strlen(word);
    // walk on the trie nodes following the word characters
    while (i < len && current != NULL && current->next != NULL) {
        current = current->next[get_char_index(word[i])];
        i++;
    }
    if (i == len && current != NULL) {
        return current->end;
    }
    return false;
}

void insert_word(trie* trie, char* word) {
    if (trie->head == NULL) {
        trie->head = malloc(sizeof(trie_node) * 27);
    }
    int len = strlen(word);
    if (trie->head[get_char_index(word[0])] == NULL) {
        trie->head[get_char_index(word[0])] = malloc(sizeof(trie_node));
    }
    trie_node* current_node = trie->head[get_char_index(word[0])];
    for (int i = 1; i < len; i++) {
        int char_index = get_char_index(word[i]);
        if (current_node->next == NULL) {
            current_node->next = malloc(sizeof(trie_node) * 27);
        }
        if (current_node->next[char_index] == NULL) {
            current_node->next[char_index] = malloc(sizeof(trie_node));
        }
        current_node = current_node->next[char_index];
    }
    current_node->end = true;
}