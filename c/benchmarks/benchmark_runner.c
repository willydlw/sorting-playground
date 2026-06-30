#include <stdio.h>
#include <string.h>             // memcpy
#include "sorting_libs.h"

// Define the global counters required by the header 
#ifdef BENCHMARK
SortMetrics bench_metrics = {0, 0, 0, 0};
#endif 

// Define a type for sorting function pointers 
typedef void (*SortFunc)(int *, size_t);

// Struct to map a human-readable name to the function 
typedef struct{
    const char *name;
    SortFunc func;
} Algorithm;

// Helper to reset and copy a fresh array for each test 
void reset_array(int *dest, const int *source, size_t size){
    memcpy(dest, source, size * sizeof(int));
}

/*
void run_benchmark(void){
    
    RESET_COUNTERS();

    bubble_sort(test_arr, n);

#ifdef BENCHMARK
    printf("--- Bubble Sort Benchmark ---\n");
    printf("Array Size:  %zu\n", n);
    printf("Comparisons: %llu\n", compare_count);
    printf("Swaps:       %llu\n", swap_count);
#else 
    printf("Benchmarking flags not enabled during compilation\n");
#endif 
}
*/


int main(void){
    // List of algorithms to benchmark.
    Algorithm algos[] = {
        {"Bubble Sort", bubble_sort},
        {"Selection Sort", selection_sort}
    };

    size_t num_algos = sizeof(algos) / sizeof(algos[0]);

    // Baseline dataset 
    const int original[] = {64, 34, 25, 12, 22, 11, 90};
    size_t n = sizeof(original)/sizeof(original[0]);
    int working[n];

    printf("%-20s | %-12s | %-12s\n", "Algorithm", "Comparisons", "Swaps");
    printf("-------------------------------------------------------\n");

    // Loop through and benchmark each algorithm 
    for(size_t i = 0; i < num_algos; i++){
        reset_array(working, original, n);
        RESET_COUNTERS();

        // call the algorithm via its function pointer 
        algos[i].func(working, n);

    #ifdef BENCHMARK 
        printf("%-16s | %-9llu | %-6llu | %-7llu | %-8llu\n",
        algos[i].name,
        bench_metrics.compare_count,
        bench_metrics.swap_count,
        bench_metrics.read_count, 
        bench_metrics.write_count );
    #else 
        printf("%-20s | Benchmarking flags not enabled.\n", algos[i].name);
    #endif 
    }

    return 0;
}

/*

To compile the benchmark executable, include the -DBENCHMARK flag so the macros actively count operations.

gcc -DBENCHMARK -Ilib/include lib/src/bubble_sort.c benchmark/sort_benchmark.c -o benchmark_runner

To compile tests or visualizations:

gcc -Ilib/include lib/src/bubble_sort.c test/test_runner.c -o test_runner


*/