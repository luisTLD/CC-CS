#ifndef SelectionSort_h
#define SelectionSort_h

#include "Swap.h"

// SelectionSort -> n^2
void selectionSort(int array[], int length)
{
    for ( int i = 0; i < length - 1; i++ )
    {
        int lowest = i;
        for ( int j = i + 1; j < length; j++ )
        {
            if ( array[lowest] > array[j] )
            {
                lowest = j;
            }
        }
        swap(array, i, lowest);
    }
}


// DoubleSelectionSort -> n^2 (Better)
void SelectionSortOpt(int array[], int length)
{
    int left = 0;
    int right = length;

    while (left < right)
    {
        int lowest = left;
        int max = left;

        for (int i = left; i < right; i++)
        {
            if (array[i] < array[lowest]) lowest = i;
            if (array[i] > array[max]) max = i;
        }

        swap(array, lowest, left);
        
        // Se o valor maximo esteve na posição inserimos o minimo, corrigir os indices
        if (max == left)  max = lowest;

        swap(array, max, right - 1);

        left++;
        right--;
    }

}


#endif
