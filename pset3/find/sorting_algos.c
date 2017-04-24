/**
 * sorting_algos.h
 * 
 * Implementations of sorting algorithms
 * 
 **/
#include <stdbool.h>
#include "sorting_algos.h"

void replace(int values[], int i, int j);
int find_min_index(int values[], int n, int start);

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
    int swap_count;
    do {
        swap_count = 0;
        //check each adjacent pair for unorder
        for (int i=0; i < n-1; i++)
        {
            //swap if needed
            if (values[i] > values[i+1])
            {
                replace(values, i, i+1);
                swap_count++;
            }
        }
    } while (swap_count != 0);
}

void order_next_element(int values[], int n, int i);

void insertion_sort(int values[], int n)
{
    //values[0..i-1] are sorted
    for (int i=1; i<n; i++)
    {
        order_next_element(values, n, i);
    }
}

void order_next_element(int values[], int n, int i)
{
    bool flag = values[i-1] > values[i];
    //values[j..i] > values[swap_index]
    for (int j=i-1; j>=0 && flag; j--)
    {
        replace(values, j, j+1);
        flag = values[j-1] > values[j]; 
    }
}