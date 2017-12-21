#include <stdbool.h>

typedef struct trie_node 
{
    struct trie_node** next;
    bool end;
} trie_node;

typedef struct trie 
{
    trie_node** head;
} trie;

bool is_word_in_trie(const trie* trie, char* word);

void insert_word(trie* trie, char* word);

void unload_trie(trie* trie);
