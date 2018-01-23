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
trie_node* init_node();
int get_char_index(char c);

bool is_word_in_trie(const trie* trie, const char* word);

void insert_word(trie* trie, char* word, int len);

bool unload_trie(trie* trie);
