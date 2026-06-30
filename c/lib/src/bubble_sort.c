#include <stdbool.h>
#include "sorting_libs.h" 


 void bubble_sort(int *arr, size_t n)
 {
    // Safety check for null array pointer or a small array that is already 
    // sorted by default. 
    if (arr == NULL || n < 2){
        return;
    }

    // The outer loop controls the maximum number of iterations
    // The index i also represents the number of elements that have been sorted
    for(size_t i = 0; i < n - 1; i++){
        // Optimize by adding an early exit flag 
        bool swapped = false;

        // The inner loop controls which pairs are compared
        // Always restarts at 0
        // i is the number of elements already sorted so we stop the inner loop
        // iteration before entering the sorted portion of the array
        for(size_t j = 0; j < n - i - 1; j++){
            
            RECORD_COMPARE();
            if(arr[j] > arr[j+1]){
                RECORD_SWAP();
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }

        if (!swapped){
            return;         // array is sorted when no pairs are swapped
        }
    }
 }
