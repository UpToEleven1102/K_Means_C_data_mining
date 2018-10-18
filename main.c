#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include "lib/utilities.h"

void generateDataPoint(int dim, int ndata, double *data) {
    for (int i = 0; i < dim * ndata; ++i) {
        data[i] = (double)(rand()%10)/10;
    }
}

int main() {
    srand(time(NULL));
    const int DIM = 2;
    const int N_DATA= 100;
    const int K = 8;

    double *data;
    data = (double *)malloc(DIM*N_DATA * sizeof(double));

    generateDataPoint(DIM, N_DATA, data);

    printArray(DIM*N_DATA, data);
    return 0;
}