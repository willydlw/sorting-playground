#include <stdio.h>
#include <stdbool.h>
#include "sorting_libs.h" 

// gcc tests/test_runner.c -Ilib/include -Llib -lsorting -o tests/run_tests

// Helper function to check if an array is sorted in ascending order
bool is_sorted(const int *arr, size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// Test case 1: Standard unsorted array
void test_bubble_sort_standard(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, n);

    if (is_sorted(arr, n)) {
        printf("[ PASS ] test_bubble_sort_standard\n");
    } else {
        printf("[ FAIL ] test_bubble_sort_standard\n");
    }
}

// Test case 2: Array that is already sorted (edge case)
void test_bubble_sort_already_sorted(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, n);

    if (is_sorted(arr, n)) {
        printf("[ PASS ] test_bubble_sort_already_sorted\n");
    } else {
        printf("[ FAIL ] test_bubble_sort_already_sorted\n");
    }
}

int main(void) {
    printf("--- Running Sorting Algorithm Tests ---\n");
    
    test_bubble_sort_standard();
    test_bubble_sort_already_sorted();
    
    printf("---------------------------------------\n");
    return 0;
}
