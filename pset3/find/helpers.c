/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"
#include "sorting_algos.h"

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
    insertion_sort(values, n);
}


