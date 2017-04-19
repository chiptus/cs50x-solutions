#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

void test_search(int values[]);
void test_sort(int values[]);

void return_false_if_n_is_negative(int values[]);
void return_true_if_val_is_in_values(int values[]);
void return_false_if_val_is_not_in_values(int values[]);
void sort_from_small_to_large(int values[]);

int main(void) {
    int values[10] = {36623, 9397, 47119, 41858, 5706, 24921, 64447, 60790, 48236, 7389};
    test_search(values);
    test_sort(values);
}

void test_search(int values[]){
    return_false_if_n_is_negative(values);
    return_true_if_val_is_in_values(values);
    return_false_if_val_is_not_in_values(values);
}

void test_sort(int values[]){
    sort_from_small_to_large(values);
}

void return_false_if_n_is_negative(int values[]) {
    printf("\nSearch() should return false when n is negative: ");
    if (search(10, values, -10)) {
        printf("FAIL\n");
    }
    printf("SUCCESS\n");
}

void return_true_if_val_is_in_values(int values[]){
    printf("\nSearch() should return true when val is in values: ");
    if (search(9397, values, 10)) {
        printf("SUCCESS\n");
    }
    printf("FAIL\n");
}

void return_false_if_val_is_not_in_values(int values[]){
    printf("\nSearch() should return false when val is not in values: ");
    if (search(10, values, 10)) {
        printf("FAIL\n");
    }
    printf("SUCCESS\n");
}

void sort_from_small_to_large() {
    
}