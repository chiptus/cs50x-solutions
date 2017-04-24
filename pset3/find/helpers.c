/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

void replace(int values[], int i, int j);
bool naive_search(int value, int values[], int n);

/**
 * Returns true if value is in array of n values, else false.
 */
 //TODO implementation is O(n)
bool search(int value, int values[], int n)
{
    return naive_search(value, values, n);
}

bool naive_search(int value, int values[], int n)
{
    bool found = false;
    for (int i=0; i<n && !found; i++) {
        found = values[i] == value;
    }
    return found;
}

/**
 * Sorts array of n values from small to big.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for (int i=0; i<n; i++) {
        for (int j=i+1; j < n; j++) {
            if (values[i] > values[j]) {
                replace(values, i, j);
            }
        }
    }
    return;
}

void replace(int values[], int i, int j) {
    int temp = values[i];
    values[i] = values[j];
    values[j] = temp;
}
