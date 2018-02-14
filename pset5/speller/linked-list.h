#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list {
    struct node * head;
    int count;
} list;

typedef struct node {
    struct node* next;
    char* value;
} node;

list* init_list();

node* init_node(const char* value);

void insert_to_top(list* l, const char* value);

void unload_list(list* l);

void print_list(list* l);

node* find_in_list(list* l, const char* value);

#endif