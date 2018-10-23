#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "K_means.h"
#include "utilities.h"

bool isACentroid(int dim, int n_cluster, double **cluster_centroid, double *datum) {
    for (int i = 0; i < n_cluster; ++i) {
        if(compareDataPoint(dim, cluster_centroid[i], datum) ==0){
            return true;
        }
    }
    return false;
}

dataPoint *findNextClusterCenter(int dim, int n_cluster, int ndata, double **cluster_centroid, double *data) {
    double *minDistanceDataPoints;
    minDistanceDataPoints = (double *) malloc(ndata * sizeof(double));
    int nextClusterIdx = 0;
    double maxDistance = 0;

    for (int i = 0; i < n_cluster; ++i) {
        minDistanceDataPoints[i] = 9999;
    }

    for (int i = 0; i < ndata; ++i) {
        double *datum = getElement(i, dim, data)->data;
        if(isACentroid(dim, n_cluster,cluster_centroid, datum)){
            continue;
        }
        for (int j = 0; j < n_cluster; ++j) {
            double distance = distanceOf2Points(dim, cluster_centroid[j], datum);
            if (minDistanceDataPoints[i] > distance) {
                minDistanceDataPoints[i] = distance;
            }
        }
        if (maxDistance < minDistanceDataPoints[i]) {
            maxDistance = minDistanceDataPoints[i];
            nextClusterIdx = i;
        }
    }

    return getElement(nextClusterIdx, dim, data);
}

int initial_centers(int dim, int ndata, double *data, int k, double **cluster_centroid) {
    int counter = 1;
    cluster_centroid[0] = getElement(rand() % k, dim, data)->data;
    while (counter < k) {
        cluster_centroid[counter] = findNextClusterCenter(dim, counter, ndata, cluster_centroid, data)->data;
        counter++;
    }
}

double *newClusterCentroid(int dim, int cluster_size, metaData *cluster_info, double *data) {
    dataPoint *newCentroid = newDataPoint(dim);
    int counter = 0;
    while (cluster_info != NULL) {
        counter++;
        printf("%d \n", cluster_info->idx);
        dataPoint *element = getElement(cluster_info->idx, dim, data);
        for (int i = 0; i < dim; ++i) {
            newCentroid->data[i] += element->data[i];
        }
        cluster_info = cluster_info->next;
    }

    for (int i = 0; i < dim; ++i) {
        newCentroid->data[i] = newCentroid->data[i] / cluster_size;
    }

    return newCentroid->data;
}

int removeCluster(int dim, int n_cluster, int idx, metaData **cluster_info, int *cluster_size) {
    for (int i = idx; i < n_cluster - 1; ++i) {
        cluster_info[i] = cluster_info[i + 1];
        cluster_size[i] = cluster_size[i + 1];
    }
}

double findClusterRadius(int dim, int cluster_start, int cluster_size, double *cluster_centroid, double *data) {
    double result = 0;
    for (int i = cluster_start; i < cluster_start + cluster_size; ++i) {
        double *datum = getElement(i, dim, data)->data;
        double distance = distanceOf2Points(dim, datum, cluster_centroid);
        if (distance> result) {
            result = distance;
        }
    }
    return result;
}

int rearrangeData(int dim, int ndata, int n_cluster, double** cluster_centroids, double *data, metaData **cluster_info, const int *cluster_size,
                  int *cluster_start,
                  double *cluster_radius) {
    double *cluster_assign = (double *) malloc(dim * ndata * sizeof(double));
    int idx = 0;
    cluster_start[0] = 0;
    for (int i = 0; i < n_cluster; ++i) {
        if (i < n_cluster - 1)
            cluster_start[i + 1] = cluster_start[i] + cluster_size[i];
        while (cluster_info[i] != NULL) {
            double *datum = getElement(cluster_info[i]->idx, dim, data)->data;
            for (int j = 0; j < dim; ++j) {
                cluster_assign[idx * dim + j] = datum[j];
            }
            idx++;
            cluster_info[i] = cluster_info[i]->next;
        }
    }
    for (int i = 0; i < dim*ndata; ++i) {
        data[i] = cluster_assign[i];
    }

    for (int i = 0; i < n_cluster; ++i) {
        cluster_radius[i] = findClusterRadius(dim, cluster_start[i], cluster_size[i], cluster_centroids[i], data);
    }
}


int K_Means(int dim, int ndata, double *data, int k, int *cluster_start, int *cluster_size, double *cluster_radius,
            double **cluster_centroid) {
    metaData **cluster_info;
    cluster_info = (metaData **) malloc(k * sizeof(metaData *));

    initial_centers(dim, ndata, data, k, cluster_centroid);

    int n_cluster = k;
    int cluster_idx = 0;
    double distance;
    bool noChange = true;

    while (true) {
        noChange = true;
        for (int i = 0; i < n_cluster; ++i) {
            cluster_info[i] = NULL;
            cluster_size[i] = 0;
        }
        for (int i = 0; i < ndata; ++i) {
            double *datum = getElement(i, dim, data)->data;
            distance = 999999;
            for (int j = 0; j < n_cluster; ++j) {
                double tempDistance = distanceOf2Points(dim, datum, cluster_centroid[j]);
                if (distance > tempDistance) {
                    cluster_idx = j;
                    distance = tempDistance;
                }
            }
            //found cluster idx for data at index i
            cluster_size[cluster_idx]++;
            metaData *dataInfo = (metaData *) malloc(sizeof(metaData));
            dataInfo->idx = i;
            if (cluster_info[cluster_idx] == NULL) {
                cluster_info[cluster_idx] = dataInfo;
                dataInfo->next = NULL;
            } else {
                dataInfo->next = cluster_info[cluster_idx];
                cluster_info[cluster_idx] = dataInfo;
            }
        }

        for (int i = 0; i < n_cluster; ++i) {
            printf("cluster %d--\n", i);
            if (cluster_info[i] == NULL) {
                //remove cluster that doesn't have any data point attached to it
                n_cluster--;
                removeCluster(dim, n_cluster, i, cluster_info, cluster_size);
                i--;
            } else {
                double *newCentroid = newClusterCentroid(dim, cluster_size[i], cluster_info[i], data);
                if (compareDataPoint(dim, newCentroid, cluster_centroid[i]) != 0) {
                    cluster_centroid[i] = newCentroid;
                    noChange = false;
                }
            }
        }

        if (noChange) {
            rearrangeData(dim, ndata, n_cluster, cluster_centroid, data, cluster_info, cluster_size, cluster_start, cluster_radius);
            break;
        }
    }
    return n_cluster;
}