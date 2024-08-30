#ifndef BubbleSort_h
#define BubbleSort_h

#include "Swap.h"

// BubbleSort -> n^2
void bubbleSort(int array[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            if (array[j] > array[j+1])
            {
                swap(array, j, j + 1);
            }
        }
    }
}

// BubbleSort with last swap saved
void bubbleSortOpt(int array[], int length)
{
    int last_swap = length - 1;
    for (int i = 0; i < length - 1; i++)
    {
        int new_last_swap = 0;
        for (int j = 0; j < last_swap; j++)
        {
            if (array[j] > array[j + 1])
            {
                swap(array, j, j + 1);
                new_last_swap = j;
            }
        }
        if (!new_last_swap)
        {
            i = length;
        }
        else
        {
            last_swap = new_last_swap;
        }
    }
}


#endif