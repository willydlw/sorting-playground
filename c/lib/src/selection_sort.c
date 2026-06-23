#include "sorting_libs.h" 

 void selection_sort(int *arr, size_t n)
 {
    for(size_t i = 0; i < n; i++){
        for(size_t j = i + 1; j < n; j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
 }