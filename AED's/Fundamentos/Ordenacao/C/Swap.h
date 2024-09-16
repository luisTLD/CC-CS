#ifndef SWAP_H
#define SWAP_H

// just a swap
void swap(int array[], int i, int j)
{
    int aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}

#endif