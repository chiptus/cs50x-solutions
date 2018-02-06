#include <stdio.h>
#include "hash-table.h"

int main() {
    //emtpy list
    hash_table* t = init_table();
    //check if empty
    printf("should be false: %i", is_word_in_table(t, "hello"));
    printf("should be zero: %i", t->count);
    //insert word
    insert_word(t, "hello", 5);
    printf("should be true: %i", is_word_in_table(t, "hello"));
    printf("should be one: %i", t->count);
    
    unload_table(t);
}