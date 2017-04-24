/**
 * sorting_algos.h
 * 
 * Implementations of sorting algorithms
 * 
 **/

#include "sorting_algos.h"

void naive_sort(int values[], int n)
{
    for (int i=0; i<n; i++) {
        for (int j=i+1; j < n; j++) {
            if (values[i] > values[j]) {
                replace(values, i, j);
            }
        }
    }
    return;
}

void selection_sort(int values[], int n)
{
    //values[0..i-1] is sorted
    // values[0..i-1] <= values[i..n]
    for (int i=0; i<n; i++) {
        //find the minimum value of values[i..n]
        int min_index = find_min_index(values, n, i);
        replace(values, i, min_index);
    }
}



int find_min_index(int values[], int n, int start)
{
    int min_index = start;
    //min_index is the smallest of values[start..j-1]
    for (int j=start+1; j < n; j++) {
        if (values[j] < values[min_index]){
            min_index = j;
        }
    }
    return min_index;
}

void replace(int values[], int i, int j)
{
    int temp = values[i];
    values[i] = values[j];
    values[j] = temp;
}

void bubble_sort(int values[], int n)
{
    
}