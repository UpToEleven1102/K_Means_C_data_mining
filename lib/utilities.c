#include <stdio.h>
#include <malloc.h>
#include "utilities.h"

double square(double n){
    return n*n;
}

int printArray(int size, double *array){
    for (int i = 0; i < size; ++i) {
        printf("%f \n",array[i]);
    }
}

dataPoint* newDataPoint(int dim){
    dataPoint *newDataPoint;
    newDataPoint = (dataPoint*)malloc(sizeof(dataPoint));
    newDataPoint->data = (double*) malloc(dim * sizeof(double));
    for (int i = 0; i < dim; ++i) {
        newDataPoint->data[i] = 0;
    }

    return newDataPoint;
}

dataPoint *getElement(int index, int dim, double *data){
    dataPoint *element = newDataPoint(dim);
    for (int i = index * dim; i < index*dim + dim ; ++i) {
        element->data[i - index*dim] = data[i];
    }
    return element;
}

void printDataSet(int dim, int ndata, double *data) {
    for (int i = 0; i < ndata; ++i) {
        printf("--%d--\n", i);
        printArray(dim, getElement(i, dim, data)->data);
    }
}