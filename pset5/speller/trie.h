

typedef struct trie_node 
{
    char value;
    struct trie_node* next;
    int end;
} trie_node;

typedef struct trie 
{
    trie_node* head;
} trie;

int is_word_in_trie(const trie* trie, char* word);

void insert_word(trie* trie, char* word);


