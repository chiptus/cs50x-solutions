typedef struct list {
    struct node * head;
    int count;
} list;

typedef struct node {
    struct node* next;
    char* value;
} node;

list* init_list();

node* init_node(char* value);

void insert_to_top(list* l, char* value);

void unload_list(list* l);

void print_list(list* l);