#ifndef SelectionSort_h
#define SelectionSort_h

#include "Swap.h"

// SelectionSort -> n^2
void selectionSort(int array[], int length)
{
    int lowest = 0;
    for (int i = 0; i < length - 1; i++)
    {
        lowest = i;
        for (int j = i + 1; j < length; j++)
        {
            if (array[lowest] > array[j])
            {
                lowest = j;
            }
        }
        swap(array, i, lowest);
    }
}


#endif