#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include "lib/utilities.h"
#include "lib/K_means.h"
#include "lib/search_KMeans.h"

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
    int k = 8;

    double *data;
    data = (double *)malloc(DIM*N_DATA * sizeof(double));

    //outputs
    int *cluster_start, *cluster_size;
    cluster_start = (int*) malloc(k * sizeof(int));
    cluster_size = (int*) malloc(k * sizeof(int));

    double * cluster_radius;
    cluster_radius = (double*) malloc(k * sizeof(double));

    double **cluster_centroid;
    cluster_centroid = (double **) malloc(k * sizeof(double*));
    for (int i = 0; i < k; ++i) {
        cluster_centroid[i] = (double*) malloc(DIM * sizeof(double));
    }

    generateDataSet(DIM, N_DATA, data);
    printDataSet(DIM, N_DATA, data);

    k = K_Means(DIM, N_DATA, data, k, cluster_start, cluster_size, cluster_radius, cluster_centroid);

    double *query_pt = (double*)malloc(DIM*sizeof(double));
    for (int i = 0; i < DIM; ++i) {
        query_pt[i] = (double) (rand()%10)/10;
    }
    double *result_pt;
    result_pt = (double*) malloc(DIM*sizeof(double));
    int counter = search_K_Means(DIM, N_DATA, data, k, cluster_start, cluster_size, cluster_radius, cluster_centroid, query_pt, result_pt);

    printf("Counter: %d\n", counter);

    printf("closet pointer: \n");

    printArray(DIM, result_pt);

    free(data);
    free(cluster_start);
    free(cluster_size);
    free(cluster_radius);
    for (int i = 0; i < k; ++i) {
        free(cluster_centroid[i]);
    }
    free(cluster_centroid);
    free(query_pt);
    free(result_pt);

    return 0;
}