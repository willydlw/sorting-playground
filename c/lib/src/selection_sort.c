#include "sorting_libs.h" 

 void selection_sort(int *arr, size_t n)
 {
    for(size_t i = 0; i < n; i++){
        size_t min_index = i;
        // cache the current minimum value to avoid redundant array reads
        int min_val = arr[ARR_READ(i)];

        for(size_t j = i + 1; j < n; j++){
            RECORD_COMPARE();
            int current_val = arr[ARR_READ(j)];
            if(current_val < min_val){
                min_val = current_val;
                min_index = j;
            }
        }

        // only swap if a smaller value was found
        if(min_index != i){
            RECORD_SWAP();
            // read value at i since we are overwriting it
            int temp = arr[ARR_READ(i)];

            // perform the two memory writes for the swap
            arr[ARR_WRITE(i)] = min_val;
            arr[ARR_WRITE(min_index)] = temp;
        }
    }
 }