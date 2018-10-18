#ifndef K_MEANS_UTILITIES_H
#define K_MEANS_UTILITIES_H

typedef struct dataPoint dataPoint;

struct dataPoint {
    double *data;
};

int printArray(int size, double *array);
void printDataSet(int dim, int ndata, double *data);
dataPoint *getElement(int index, int dim, double *data);

#endif //K_MEANS_UTILITIES_H
