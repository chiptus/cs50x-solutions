#include <stdbool.h>

typedef struct trie_node 
{
    struct trie_node* next[27];
    bool end;
} trie_node;

typedef struct trie 
{
    trie_node* head[27];
} trie;

trie* init_trie();

bool is_word_in_trie(const trie* trie, const char* word);

void insert_word(trie* trie, char* word);

bool unload_trie(trie* trie);
