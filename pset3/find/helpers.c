/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

bool naive_search(int value, int values[], int n);
bool binary_search(int value, int values[], int n);
bool binary_search_rec(int value, int values[], int n, int start, int end);

void merge_sort(int values[], int n);
void merge_sort_rec(int values[], int n, int start, int end);
void merge(int values[], int start, int mid, int end);
void copy_arr(int values[], int newArr[], int start, int len);
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


void merge_sort(int values[], int n)
{
    merge_sort_rec(values, n, 0, n);
}

/*
    recursive function for merge sort
    params:
    values - array to sort
    n - length of array
    start - from where to sort
    end - until where to sort (exclusive)
*/
void merge_sort_rec(int values[], int n, int start, int end)
{
    if ((start == end) || (start == end - 1) || (start > end)) {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort_rec(values, n, start, mid);
    merge_sort_rec(values, n, mid, end);
    merge(values, start, mid, end);
}

//merge values[start..mid-1] and values[mid..end] so that values[start..end] is sorted
//values[start..mid-1] and values[mid..end] are sorted
void merge(int values[], int start, int mid, int end)
{
    int len_right = end - mid;
    int len_left = mid - start;
    
    //copy the parts of the array to new arrays   
    int left[len_left];
    copy_arr(values, left, start, len_left);
    
    int right[len_right];
    copy_arr(values, right, mid, len_right);
    
    int i = 0;
    int j = 0;
    int k = start;
    //compare both arrays and put from small to large
    while (i < len_left && j < len_right){
        if (left[i] < right[j]) {
            values[k] = left[i];
            i++;
        } 
        else {
            values[k] = right[j];
            j++;
        }
        k++;
    }
    //values[start..k-1] < remaining values in both arrays
    //one of the arrays was already passed on.
    
    //add remaining values from left array
    while (i < len_left) {
        values[k] = left[i];
        i++;
        k++;
    }
    while (j < len_right) {
        values[k] = right[j];
        j++;
        k++;
    }
}

//copy values[start..start+len-1] into newArr[0..len-1]
void copy_arr(int values[], int newArr[], int start, int len)
{
    for (int i=0; i < len; i++)
    {
        newArr[i] = values[start + i];
    }
}

