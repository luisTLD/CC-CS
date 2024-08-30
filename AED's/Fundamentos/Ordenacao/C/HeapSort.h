#ifndef HeapSort_h
#define HeapSort_h

#include "Swap.h"

// HeapSort -> n.log(n)
void heapSort(int array[], int length)
{
    int endIndex = length - 1;
    for (int max = 1; max < length; max++)
    {
        makeHeap(array, max);
    }

    while (endIndex > 0)
    {
        swap(array, 0, endIndex);
        endIndex--;
        redoHeap(array, endIndex);
    }

}
// Montar o array em formato de heap
void makeHeap(int array[], int max)
{
    for (int i = max; max > 0 && array[i] > array[(i-1)/2]; i = (i-1)/2)
    {
        swap(array, i, (i-1)/2);
    }
}
// Remontar o heap
void redoHeap(int array[], int endIndex)
{
    int aux = 0;
    while (hasSon(aux, endIndex))
    {
        int son = getBiggerSon(array, aux, endIndex);
        if (array[aux] < array[son])
        {
            swap(array, aux, son);
            aux = son;
        }
        else break;
    }
}
// 1 caso tenha filho / 0 caso nao tenha
int hasSon(int aux, int endIndex)
{
    int ver = 0;
    if (((aux*2)+1) <= endIndex) ver = 1;
    return ver;
}
// Retornar maior filho
int getBiggerSon(int array[], int aux, int endIndex)
{
    int son = 0;
    if ( ((2*aux)+1) == endIndex ) son = endIndex;
    else if (array[(2*aux)+1] > array[(2*aux)+2]) son = ((2*aux)+1);
    else son = ((2*aux)+2);
    return son;
}


#endif