#ifndef Swap_h
#define Swap_h

// just a swap
void swap(int array[], int i, int j)
{
    int aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}

#endif