#ifndef InsertionSort_h
#define InsertionSort_h

void swap(int array[], int i, int j);



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

void swap(int array[], int i, int j)
{
    int aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}



#endif