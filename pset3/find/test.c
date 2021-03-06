#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

void test_search(int values[], int len);
void test_sort(int values[], int len);

void print_array(int arr[], int n);

void return_false_if_n_is_negative(int values[]);
void return_true_if_val_is_in_values(int values[], int len);
void return_false_if_val_is_not_in_values(int values[], int len);
void sort_from_small_to_large(int values[], int len);

bool small_to_large(int values[], int len);
void test_small_to_large();
void return_true_if_values_is_sorted_from_small_to_large();
void return_false_if_values_is_not_sorted_from_small_to_large();

int main(void) {
    int values[10] = {36623, 9397, 47119, 41858, 5706, 24921, 64447, 60790, 48236, 7389};
    test_search(values, 10);
    test_sort(values, 10);
    test_small_to_large();
}

void test_search(int values[], int len){
    return_false_if_n_is_negative(values);
    return_true_if_val_is_in_values(values, len);
    return_false_if_val_is_not_in_values(values, len);
}

void test_sort(int values[], int len){
    sort_from_small_to_large(values, len);
}

void return_false_if_n_is_negative(int values[]) {
    printf("\nSearch() should return false when n is negative: ");
    if (search(10, values, -10)) {
        printf("FAIL\n");
        return;
    }
    printf("SUCCESS\n");
}

void return_true_if_val_is_in_values(int values[], int len){
    printf("\nSearch() should return true when val is in values: ");
    if (search(9397, values, len)) {
        printf("SUCCESS\n");
        return;
    }
    printf("FAIL\n");
}

void return_false_if_val_is_not_in_values(int values[], int len){
    printf("\nSearch() should return false when val is not in values: ");
    if (search(10, values, len)) {
        printf("FAIL\n");
        return;
    }
    printf("SUCCESS\n");
}

void sort_from_small_to_large(int values[], int len) {
    printf("\nsort() should sort values from small to large: ");
    sort(values, len);
    if (small_to_large(values, len)) {
        printf("SUCCESS\n");
        return;
    }
    printf("FAIL, returned array is: \n");
    print_array(values, len);
    printf("\n");
}

bool small_to_large(int values[], int len) {
    bool flag = true;
    for (int i=1; i < len && flag; i++) {
        flag = values[i-1] < values[i];
    }
    return flag;
}

void test_small_to_large(){
    return_true_if_values_is_sorted_from_small_to_large();
    return_false_if_values_is_not_sorted_from_small_to_large();
}
void return_true_if_values_is_sorted_from_small_to_large(){
    printf("\nsmall_to_large() should return true if values is sorted from small to large: ");
    int values[10] = {1,2,3,4,5,6,7,8,9,10};
    if (small_to_large(values, 10)) {
        printf("SUCCESS\n");
        return;
    }
    printf("FAIL\n");
}
void return_false_if_values_is_not_sorted_from_small_to_large(){
    printf("\nsmall_to_large() should return true if values is not sorted from small to large: ");
    int values[10] = {1,4,3,4,5,6,7,8,9,10};
    if (small_to_large(values, 10)) {
        printf("FAIL\n");
        return;
    }
    printf("SUCCESS\n");
}

void print_array(int arr[], int n){
    printf("[");
    for (int i =0; i < n; i++) {
        printf("%i", arr[i]);
        if (i < n -1) {
            printf(",");
        }
    }
    printf("]");
}