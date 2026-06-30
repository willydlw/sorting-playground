#ifndef SORTING_LIBS_H
#define SORTING_LIBS_H 

#include <stddef.h>     // provides size_t 

// Struct to hold operational metrics 
typedef struct{
    unsigned long long compare_count;
    unsigned long long swap_count;
    unsigned long long read_count;
    unsigned long long write_count;
} SortMetrics;



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
    extern SortMetrics bench_metrics;

    // Benchmarking macros 
    #define RECORD_COMPARE() (bench_metrics.compare_count++)
    #define RECORD_SWAP()    (bench_metrics.swap_count++)

    // macro evaluates teh increment statement first, throws away its result,
    // and passes the rightmost statement (idx) back to the array brackets
    #define ARR_READ(idx)    ((bench_metrics.read_count++), (idx))
    #define ARR_WRITE(idx)   ((bench_metrics.write_count++), (idx))

    #define RESET_COUNTERS() do { \
        bench_metrics.compare_count = 0; \
        bench_metrics.swap_count = 0; \
        bench_metrics.read_count = 0; \
        bench_metrics.write_count = 0; \
    } while(0)
#else 
    // Compiles to nothing
    #define RECORD_COMPARE()
    #define RECORD_SWAP()

    // normal array indexing ARR_READ(j) evaluates directly to j
    // compiler optimizes it away
    #define ARR_READ(idx) (idx)
    #define ARR_WRITE(idx) (idx)

    #define RESET_COUNTERS()
#endif 

#endif /* SORTING_LIBS_H */