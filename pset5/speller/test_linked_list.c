#include "linked-list.h"

int main() {
    list* l = init_list();
    print_list(l);
    l->head = init_node("hello");
    print_list(l);
    insert_to_top(l, "chamana");
    print_list(l);
    unload_list(l);
}