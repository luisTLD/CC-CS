#ifndef InsertionSort_h
#define InsertionSort_h

#include "Swap.h"

// InsertionSort -> n^2
void insertionSort(int arr[], int length)
{
    for (int i = 1; i < length; i++)
    {
        int tmp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = tmp;
    }
}


#endif