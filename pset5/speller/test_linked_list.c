#include <stdio.h>
#include "linked-list.h"

void print_list(list* l) 
{
    node* current = l->head;
    while (current != NULL) {
        printf("%s, ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() 
{
    list* l = init_list();
    print_list(l);
    l->head = init_node("hello");
    print_list(l);
    insert_to_top(l, "chamana");
    node* n = find_in_list(l, "chamana");
    printf("shouldn't be null: %i\n", n != NULL);
    
    node* not_found_node = find_in_list(l, "nothere");
    printf("should be null: %i\n", not_found_node == NULL);
    
    
    print_list(l);
    unload_list(l);
}