#include <stdio.h>
#include "linked-list.h"

int main() {
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