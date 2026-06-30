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

/**
 * @brief Sorts an array of integers using the Selection Sort algorithm.
 * 
 * @param arr Pointer to the first elment of the integer array.
 * @param n   The number of elements in the array.
 */
void selection_sort(int *arr, size_t n);

#ifdef BENCHMARK 
    // Global operational counters 
    extern unsigned long long compare_count;
    extern unsigned long long swap_count;

    // Benchmarking macros 
    #define RECORD_COMPARE() (compare_count++)
    #define RECORD_SWAP()    (swap_count++)
    #define RESET_COUNTERS() do {compare_count = 0; swap_count = 0; } while(0)
#else 
    // Compiles to nothing
    #define RECORD_COMPARE()
    #define RECORD_SWAP()
    #define RESET_COUNTERS()
#endif 

#endif /* SORTING_LIBS_H */