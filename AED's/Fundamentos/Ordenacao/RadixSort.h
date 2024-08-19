#ifndef RadixSort_h
#define RadixSort_h

#include <stdlib.h>



// RadixSort -> n
void radixSort(int array[], int length)
{
    int max = array[0];
    for (int i = 1; i < length; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        radixCountingSort(array, length, exp);
    }
}
void radixCountingSort(int array[], int length, int exp)
{
    int* output = (int*)malloc(length * sizeof(int));
    int counting[10] = {0}; 

    for (int i = 0; i < length; i++)
    {
        counting[(array[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++)
    {
        counting[i] += counting[i - 1];
    }

    for (int i = length - 1; i >= 0; i--)
    {
        output[counting[(array[i] / exp) % 10] - 1] = array[i];
        counting[(array[i] / exp) % 10]--;
    }

    for (int i = 0; i < length; i++)
    {
        array[i] = output[i];
    }

    free(output);
}











#endif