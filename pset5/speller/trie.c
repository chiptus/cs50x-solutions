#include <stdlib.h>
#include <stdio.h>
#include "trie.h"



int main() {
    trie trie;
    int answer = is_word_in_trie(&trie, "walla");
    printf("trie should be empty %d\n", answer == 0);
    return 0;
}


int is_word_in_trie(const trie* trie, char* word) {
    return 0;
}

void insert_word(trie* trie, char* word) {
    
}