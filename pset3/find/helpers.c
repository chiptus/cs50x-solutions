/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"
#include "sorting_algos.h"

bool naive_search(int value, int values[], int n);
bool binary_search(int value, int values[], int n);
bool binary_search_rec(int value, int values[], int n, int start, int end);

/**
 * Returns true if value is in array of n values, else false.
 */
 //TODO implementation is O(n)
bool search(int value, int values[], int n)
{
    return binary_search(value, values, n);
}

bool naive_search(int value, int values[], int n)
{
    bool found = false;
    for (int i=0; i<n && !found; i++) {
        found = values[i] == value;
    }
    return found;
}


bool binary_search(int value, int values[], int n)
{
  return binary_search_rec(value, values, n, 0, n);  
}

bool binary_search_rec(int value, int values[], int n, int start, int end)
{
    //length negative
    if (start >= end) 
    {
        return false;
    }
    //length 1
    if (start == end - 1)
    {
        return (values[start] == value);
    }
    int mid = (start + end) / 2;
    return binary_search_rec(value, values, n, start, mid) ||
        binary_search_rec(value, values, n, mid, end);
    
}

/**
 * Sorts array of n values from small to big.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    merge_sort(values, n);
}


