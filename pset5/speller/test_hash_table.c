#include <stdio.h>
#include "hash-table.h"

int main() {
    //emtpy list
    hash_table* t = init_table();
    //check if empty
    printf("should be false: %i\n", is_word_in_table(t, "hello"));
    printf("should be zero: %i\n", t->count);
    //insert word
    insert_word(t, "hello", 5);
    printf("should be true: %i\n", is_word_in_table(t, "hello"));
    printf("should be one: %i\n", t->count);
    
    printf("should be true: %i\n", unload_table(t));
    
}