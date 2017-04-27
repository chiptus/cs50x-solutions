/**
 * sorting_algos.h
 * 
 * Implementations of sorting algorithms
 * 
 **/
#include <stdbool.h>
#include "sorting_algos.h"
#include <stdio.h>
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
    //values[j+1..i] and values[0..j] are sorted 
    for (int j=i-1; j>=0 && flag; j--)
    {
        replace(values, j, j+1);
        flag = values[j-1] > values[j]; 
    }
}

void merge_sort_rec(int values[], int n, int start, int end);
void merge(int values[], int start, int mid, int end);
void copy_arr(int values[], int newArr[], int start, int len);

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