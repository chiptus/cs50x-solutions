// Chaim Lando
// Problem Set 5

// Declares a linked list interface 

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Types
typedef struct node 
{
    struct node *next;
    char* value;
}
node;

typedef struct list 
{
    node *head;
    int count;
} 
list;

// Prototypes
list* init_list();
node* init_node(const char* value);
void insert_to_top(list* l, const char* value);
void unload_list(list* l);
node* find_in_list(list* l, const char* value);

#endif                                                                         