#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "K_means.h"
#include "utilities.h"

double distanceOf2Points(int dim, double *point1, double *point2) {
    double distance = 0;
    for (int i = 0; i < dim; ++i) {
        distance += square(point1[i] - point2[i]);
    }
    return sqrt(distance);
}

dataPoint *findNextClusterCenter(int dim, int k, int ndata, double **cluster_centroid, double *data) {
    double *minDistanceDataPoints;
    minDistanceDataPoints = (double*) malloc(k*sizeof(double));
    int nextClusterIdx = 0;
    double nextClusterDistance = 0;

    for (int i = 0; i < k; ++i) {
        minDistanceDataPoints[i] = 9999;
    }

    for (int i = 0; i < ndata; ++i) {
        double* datum = getElement(i, dim, data)->data;
        for (int j = 0; j < k; ++j) {
            double distance = distanceOf2Points(dim, cluster_centroid[j], datum);
            if (minDistanceDataPoints[i] > distance) {
                minDistanceDataPoints[i] = distance;
            }
        }
        if(nextClusterDistance < minDistanceDataPoints[i]) {
            nextClusterDistance = minDistanceDataPoints[i];
            nextClusterIdx = i;
        }
    }

    return getElement(nextClusterIdx, dim, data);
}

int initial_centers(int dim, int ndata, double *data, int k, double **cluster_centroid) {
    int counter = 1;
    cluster_centroid[0] = getElement(rand()%k, dim, data)->data;
    while (counter < k) {
        cluster_centroid[counter] = findNextClusterCenter(dim, counter, ndata, cluster_centroid, data)->data;
        counter ++;
    }
}

int K_Means(int dim, int ndata, double *data, int k, int *cluster_start, int *cluster_size, double *cluster_radius, double **cluster_centroid) {
    //initialize inputs:
    for (int i = 0; i < k; ++i) {
        cluster_start[i] = 0;
        cluster_size[i] = 0;
    }

    metaData **cluster_info;
    cluster_info = (metaData**) malloc(k * sizeof(metaData*));

    initial_centers(dim, ndata, data, k, cluster_centroid);
    int n_cluster = k;
    int cluster_idx = 0;
    double distance;

//    while(true) {
        for (int i = 0; i < k; ++i) {
            cluster_info[i] = NULL;
        }
        for (int i = 0; i < ndata; ++i) {
            double *datum = getElement(i, dim, data)->data;
            distance = 999999;
            for (int j = 0; j < n_cluster; ++j) {
                double tempDistance = distanceOf2Points(dim, datum, cluster_centroid[j]);
                if(distance > tempDistance) {
                    cluster_idx = j;
                    distance = tempDistance;
                }
            }
            //found cluster idx for data at index i
            cluster_size[cluster_idx]++;
            metaData *dataInfo = (metaData*)malloc(sizeof(metaData));
            dataInfo->idx = i;
            if(cluster_info[cluster_idx]==NULL) {
                cluster_info[cluster_idx] = dataInfo;
            } else {
                dataInfo->next = cluster_info[cluster_idx];
                cluster_info[cluster_idx] = dataInfo;
            }
        }

        for (int i = 0; i < n_cluster; ++i) {
            if(cluster_info[i] == NULL) {
                //get rid of the cluster
            } else {
                //calculate mean
                //reset value for cluster_size
            }
        }

    //if no change in cluster_centroid, break
//    }

}