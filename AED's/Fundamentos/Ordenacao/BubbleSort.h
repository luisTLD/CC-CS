#ifndef BubbleSort_h
#define BubbleSort_h

void swap(int array[], int i, int j);



// BubbleSort -> n^2
void bubbleSort(int array[], int length)
{
    int tmp = 0;
    for ( int i = 0; i < length - 1; i++ )
    {
        for ( int j = 0; j < length - i - 1; j++ )
        {
            if ( array[j] > array[j+1])
            {
                swap(array, j, j + 1);
            }
        }
    }
}

void swap(int array[], int i, int j)
{
    int aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}



#endif