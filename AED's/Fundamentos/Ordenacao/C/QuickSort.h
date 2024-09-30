#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Swap.h"

// QuickSort -> n.log(n) // n^2 pior caso
void quickSort(int array[], int length)
{
    quickSortCall(array, 0, length - 1);
}
// Chamada recursiva p/ quickSort
void quickSortCall(int array[], int left, int right)
{
    int i = left;
    int j = right;
    int piv = array[(left + right)/2];
    while ( j >= i )
    {
        while ( array[i] < piv ) i++;
        while ( array[j] > piv ) j--;

        if ( j >= i ) 
        {
            swap(array, i, j);
            i++;
            j--;
        }
    }
   
    if ( left < j ) quickSortCall(array, left, j);
    if ( right > i ) quickSortCall(array, i, right);
}


#endif