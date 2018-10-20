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
    minDistanceDataPoints = (double *) malloc(k * sizeof(double));
    int nextClusterIdx = 0;
    double nextClusterDistance = 0;

    for (int i = 0; i < k; ++i) {
        minDistanceDataPoints[i] = 9999;
    }

    for (int i = 0; i < ndata; ++i) {
        double *datum = getElement(i, dim, data)->data;
        for (int j = 0; j < k; ++j) {
            double distance = distanceOf2Points(dim, cluster_centroid[j], datum);
            if (minDistanceDataPoints[i] > distance) {
                minDistanceDataPoints[i] = distance;
            }
        }
        if (nextClusterDistance < minDistanceDataPoints[i]) {
            nextClusterDistance = minDistanceDataPoints[i];
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

    while (cluster_info != NULL) {
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

int compareDataPoint(int dim, const double *point1, const double *point2) {
    for (int i = 0; i < dim; ++i) {
        if (point1[i] != point2[i]) {
            return -1;
        }
    }
    return 0;
}

int removeCluster(int dim, int n_cluster, int idx, metaData **cluster_info, int *cluster_size) {
    for (int i = idx; i < n_cluster - 1; ++i) {
        cluster_info[i] = cluster_info[i + 1];
        cluster_size[i] = cluster_size[i + 1];
    }
}

int rearrangeData(int dim, int ndata, int n_cluster, double *data, metaData **cluster_info, const int *cluster_size,
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
            } else {
                dataInfo->next = cluster_info[cluster_idx];
                cluster_info[cluster_idx] = dataInfo;
            }
        }

        for (int i = 0; i < n_cluster; ++i) {
            printf("cluster %d--\n", i);
            if (cluster_info[i] == NULL) {
                //get rid of the cluster
                n_cluster--;
                removeCluster(dim, n_cluster, i, cluster_info, cluster_size);
            } else {
                double *newCentroid = newClusterCentroid(dim, cluster_size[i], cluster_info[i], data);
                if (compareDataPoint(dim, newCentroid, cluster_centroid[i]) != 0) {
                    cluster_centroid[i] = newCentroid;
                    noChange = false;
                }
            }
        }

        if (noChange) {
            rearrangeData(dim, ndata, n_cluster, data, cluster_info, cluster_size, cluster_start, cluster_radius);
            break;
        }
    }
    return n_cluster;
}