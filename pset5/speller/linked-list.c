#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linked-list.h"

list* init_list() {
    return (list *)(calloc(1, sizeof(list)));
}

node* init_node(const char* value) {
    node * n = (node *)(calloc(1, sizeof(node)));;
    n->value= (char *)value;
    return n;
}

node* insert(node* n, const char* value) {
    node* new_node = init_node(value);
    new_node->next = n;
    return new_node;
}

void insert_to_top(list* l, const char* value) {
    l->head = insert(l->head, value);
    l->count++;
}

node* unload_node(node* n) {
    node* next = n->next;
    n->next = NULL;
    free(n->value);
    free(n);
    return next;
}

void unload_list(list* l) {
    node* current = l->head;
    while (current != NULL) {
        current = unload_node(current);
    }
    free(l);
}
 
node* find_in_list(list* l, const char* value) {
    node* current = l->head;
    while (current != NULL) {
        if (strcmp(current->value, value) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
