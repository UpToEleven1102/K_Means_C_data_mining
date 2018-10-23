#include <stdlib.h>
#include "search_KMeans.h"
#include "utilities.h"

double distanceDatumToCluster(int dim, double *datum, double *cluster_centroid, double cluster_radius) {
    double distance = distanceOf2Points(dim, datum, cluster_centroid);
    return distance - cluster_radius;
}

double *
findClosestPointInCluster(int dim, int *counter, double *datum, int cluster_start, int cluster_size, double *data) {
    double *closest_pt = NULL;
    double shortest_distance = 999;

    for (int i = cluster_start; i < cluster_start + cluster_size; ++i) {
        *counter = *counter + 1;
        dataPoint *element = getElement(i, dim, data);
        double distance = distanceOf2Points(dim, datum, element->data);
        if (distance < shortest_distance) {
            free(closest_pt);
            closest_pt = element->data;
        }
        free(element);
    }
    return closest_pt;
}


int
search_K_Means(int dim, int ndata, double *data, int k, int *cluster_start, int *cluster_size, double *cluster_radius,
               double **cluster_centroid, double *query_pt, double *result_pt) {
    int closest_cluster_idx = 0;
    //save distance to each cluster
    double *distances = (double *) malloc(k * sizeof(double));
    double shortest_distance = distanceDatumToCluster(dim, query_pt, cluster_centroid[0], cluster_radius[0]);

    for (int i = 1; i < k; ++i) {
        distances[i] = distanceDatumToCluster(dim, query_pt, cluster_centroid[i], cluster_radius[i]);
        if (distances[i] < shortest_distance) {
            shortest_distance = distances[i];
            closest_cluster_idx = i;
        }
    }

    int *counter = (int *) malloc(sizeof(int));
    *counter = 0;
    double *closest_point = findClosestPointInCluster(dim, counter, query_pt, cluster_start[closest_cluster_idx],
                                              cluster_size[closest_cluster_idx], data);
    shortest_distance = distanceOf2Points(dim, closest_point, query_pt);

    double distance = 0;
    double *temp_point = NULL;
    for (int i = 0; i < k; ++i) {
        if(i!=closest_cluster_idx) {
            distance = distanceDatumToCluster(dim, query_pt, cluster_centroid[i], cluster_radius[i]);
            if (distance < shortest_distance) {
                temp_point = findClosestPointInCluster(dim, counter, query_pt, cluster_start[i], cluster_size[i], data);
                distance = distanceOf2Points(dim, query_pt, temp_point);
                if(distance < shortest_distance) {
                    shortest_distance = distance;
                    closest_point = temp_point;
                }
            }
        }
    }

    for (int i = 0; i < dim; ++i) {
        result_pt[i] = closest_point[i];
    }

    int count = *counter;
    free(closest_point); free(counter); free(temp_point); free(closest_point); free(distances);
    return count;
}
