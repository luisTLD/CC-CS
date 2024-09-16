#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H


int binarySearchInsertion(int array[], int right, int key)
{
    int left = 0;
    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (array[middle] == key)
        {
            return middle + 1;
        }
        else if (array[middle] > key)
        {
            right = middle - 1;
        }
        else 
        {
            left = middle + 1;
        }
    }
    return left;
}

// InsertionSort with binary search (N log(N) comp / n^2 moves)
void insertionSortOpt(int array[], int length)
{
    for (int i = 1; i < length; i++)
    {
        int tmp = array[i];
        int j = i - 1;
        int locate = binarySearchInsertion(array, i, array[i]);
        while (j >= locate)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = tmp;
    }
}

// InsertionSort -> n^2
void insertionSort(int array[], int length)
{
    for (int i = 1; i < length; i++)
    {
        int tmp = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > tmp)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = tmp;
    }
}


#endif