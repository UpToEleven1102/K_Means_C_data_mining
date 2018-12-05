# KDMeans_C_DataMining ReadMe File
Data Mining & High Performance Computing
 10/24/2018


## File compilation

Windows
GNU bash, version 4.1.11(2)-release (x86_64-unknown-cygwin)
```
gcc main.c lib/utilities.c lib/K_means.c lib/search_KMeans.c -o KMeans -std=gnu99
```
run ```KMeans.exe``` file in Windows

Ubuntu Linux 18.04 LTS
gcc version 7.3.0 (Ubuntu 7.3.0-16ubuntu3)
```
gcc main.c ./lib/utilities.c ./lib/K_means.c lib/search_KMeans.c -std+gnu99 -o kdtree
```
run ```./k_means``` in ubuntu




## K_means.c Documentation

- initializes initial k cluster centroids: to find next centroid, among data points that has the smallest distance to all existing cluster, pick the data point that has largest value
- goes through the data set and arrange each data point into the cluster of the closest centroid
- recalculate the cluster centroids: for each cluster, find the means of all the data point within a cluster and assign it to be new centroid
- repeat step 2 and 3 until no change for all cluster centroids

## search_KMeans.c Documentation

- find the closest cluster to the query point using formular: distance = distance(query_pt, cluster_centroid) - cluster_radius
- exhausted search all elements inside the cluster to find the closest data point
- for all clusters that have distance to the query point less than the distance from the query point to the data point found in the previous step, exhausted search to find better data point.

## utilities.c Documentation

utilities.c is a group of helper functions used to facilitate the coding process
