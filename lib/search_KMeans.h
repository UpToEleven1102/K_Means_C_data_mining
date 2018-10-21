#ifndef K_MEANS_SEARCH_KMEANS_H
#define K_MEANS_SEARCH_KMEANS_H

int search_K_Means(int dim, int ndata, double *data, int k, int *cluster_start, int *cluster_size, double *cluster_radius,
                   double **cluster_centroid, double *query_pt, double *result_pt);

#endif //K_MEANS_SEARCH_KMEANS_H
