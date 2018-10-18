cmake_minimum_required(VERSION 3.12)
project(K_Means C)

set(CMAKE_C_STANDARD 99)

add_executable(K_Means main.c lib/K_means.c lib/K_means.h lib/utilities.c lib/utilities.h)