#include <stdlib.h>
#include <stdio.h>

#include "linked-list.h"

list* init_list() {
    return (list *)(calloc(1, sizeof(list)));
}

node* init_node(char* value) {
    node * n = (node *)(calloc(1, sizeof(node)));;
    n->value=value;
    return n;
}

node* insert(node* n, char* value) {
    node* new_node = init_node(value);
    new_node->next = n;
    return new_node;
}

void insert_to_top(list* l, char* value) {
    l->head = insert(l->head, value);
    l->count++;
}


void unload_list(list* l) {
    node* current = l->head;
    while (current != NULL) {
        node* prev = current;
        current = current->next;
        prev->next = NULL;
        free(prev);
    }
    free(l);
}

void print_list(list* l) {
    node* current = l->head;
    while (current != NULL) {
        printf("%s, ", current->value);
        current = current->next;
    }
    printf("\n");
}

