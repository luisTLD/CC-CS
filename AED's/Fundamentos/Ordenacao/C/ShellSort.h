#ifndef SHELLSORT_H
#define SHELLSORT_H

void shellSort(int array[], int length)
{
    int h = 1;

    do {
        h = (h * 3) + 1;
    } while (h < length);

    do {
        h /= 3; 
        for (int part = 0; part < h; part++)
        {
            for (int i = h + part; i < length; i += h)
            {
                int tmp = array[i];
                int j = i - h;
                while (j >= 0 && array[j] > tmp)
                {
                    array[j + h] = array[j];
                    j -= h;
                }
                array[j + h] = tmp;
            }
        }
    } while (h > 1);
}

#endif