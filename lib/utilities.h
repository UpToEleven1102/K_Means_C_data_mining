#ifndef K_MEANS_UTILITIES_H
#define K_MEANS_UTILITIES_H

typedef enum {false, true} bool;

typedef struct dataPoint dataPoint;

struct dataPoint {
    double *data;
};

int printArray(int size, double *array);
void printDataSet(int dim, int ndata, double *data);
double square(double n);
dataPoint *getElement(int index, int dim, double *data);
dataPoint* newDataPoint(int dim);

#endif //K_MEANS_UTILITIES_H
