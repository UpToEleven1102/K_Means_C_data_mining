#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include "lib/utilities.h"
#include "lib/K_means.h"

void generateDataSet(int dim, int ndata, double *data) {
    for (int i = 0; i < dim * ndata; ++i) {
        data[i] = (double)(rand()%10)/10;
    }
}

int main() {
    srand(time(NULL));

    //inputs
    const int DIM = 2;
    const int N_DATA= 20;
    const int K = 4;

    double *data;
    data = (double *)malloc(DIM*N_DATA * sizeof(double));

    //outputs
    int *cluster_start, *cluster_size;
    cluster_start = (int*) malloc(K * sizeof(int));
    cluster_size = (int*) malloc(K * sizeof(int));

    double * cluster_radius;
    cluster_radius = (double*) malloc(K * sizeof(double));

    double **cluster_centroid;
    cluster_centroid = (double **) malloc(K * sizeof(double*));
    for (int i = 0; i < K; ++i) {
        cluster_centroid[i] = (double*) malloc(DIM * sizeof(double));
    }

    generateDataSet(DIM, N_DATA, data);
    printDataSet(DIM, N_DATA, data);

    K_Means(DIM, N_DATA, data, K, cluster_start, cluster_size, cluster_radius, cluster_centroid);
    return 0;
}