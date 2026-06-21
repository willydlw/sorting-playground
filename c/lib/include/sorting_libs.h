#ifndef SORTING_LIBS_H
#define SORTING_LIBS_H 

#include <stddef.h>     // provides size_t 

/**
 * @brief Sorts an array of integers using the Bubble Sort algorithm.
 * 
 * @param arr Pointer to the first elment of the integer array.
 * @param n   The number of elements in the array.
 */
 void bubble_sort(int *arr, size_t n);

#endif /* SORTING_LIBS_H */