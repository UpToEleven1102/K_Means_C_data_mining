#include <stdio.h>
#include "utilities.h"

int printArray(int size, double *array){
    for (int i = 0; i < size; ++i) {
        printf("%f \n",array[i]);
    }
}