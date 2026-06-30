#include <stdio.h>
#include "sorting_libs.h"

// Define the global counters required by the header 
#ifdef BENCHMARK
unsigned long long compare_count = 0;
unsigned long long swap_count = 0;
#endif 

void run_benchmark(void){
    int test_arr[] = {64, 34, 25, 12, 22, 11, 90};
    size_t n = sizeof(test_arr)/sizeof(test_arr[0]);

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


int main(void){
    run_benchmark();
    return 0;
}

/*

To compile the benchmark executable, include the -DBENCHMARK flag so the macros actively count operations.

gcc -DBENCHMARK -Ilib/include lib/src/bubble_sort.c benchmark/sort_benchmark.c -o benchmark_runner

To compile tests or visualizations:

gcc -Ilib/include lib/src/bubble_sort.c test/test_runner.c -o test_runner


*/