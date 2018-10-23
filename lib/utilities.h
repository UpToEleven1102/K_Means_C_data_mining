#ifndef K_MEANS_UTILITIES_H
#define K_MEANS_UTILITIES_H

typedef enum {false, true} bool;

typedef struct dataPoint dataPoint;
struct dataPoint {
    double *data;
};

typedef struct metaData metaData;
struct metaData {
    int idx;
    metaData *next;
};

int compareDataPoint(int dim, const double *point1, const double *point2);
double distanceOf2Points(int dim, double *point1, double *point2);
int printArray(int size, double *array);
void printDataSet(int dim, int ndata, double *data);
double square(double n);
dataPoint *getElement(int index, int dim, double *data);
dataPoint* newDataPoint(int dim);

#endif //K_MEANS_UTILITIES_H
