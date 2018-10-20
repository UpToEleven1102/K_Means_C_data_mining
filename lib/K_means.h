#ifndef K_MEANS_K_MEANS_H
#define K_MEANS_K_MEANS_H

typedef struct metaData metaData;
struct metaData {
    int idx;
    metaData *next;
};

int K_Means(int dim, int ndata, double *data, int k, int *cluster_start, int *cluster_size, double *cluster_radius, double **cluster_centroid);

#endif //K_MEANS_K_MEANS_H
