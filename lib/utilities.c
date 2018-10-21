#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "utilities.h"

double square(double n){
    return n*n;
}

int compareDataPoint(int dim, const double *point1, const double *point2) {
    for (int i = 0; i < dim; ++i) {
        if (point1[i] != point2[i]) {
            return -1;
        }
    }
    return 0;
}

double distanceOf2Points(int dim, double *point1, double *point2) {
    double distance = 0;
    for (int i = 0; i < dim; ++i) {
        distance += square(point1[i] - point2[i]);
    }
    return sqrt(distance);
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