#ifndef SelectionSort_h
#define SelectionSort_h

void swap(int array[], int i, int j);



// SelectionSort -> n^2
void selectionSort(int array[], int length)
{
    int lowest = 0;
    for ( int i = 0; i < length - 1; i++ )
    {
        lowest = i;
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

void swap(int array[], int i, int j)
{
    int aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}



#endif