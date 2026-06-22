#include <errno.h>          // errno and ERANGE
#include <limits.h>         // ULLONG_MAX
#include <stddef.h>         // size_t
#include <stdint.h>         // SIZE_MAX
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>         // srand, rand, malloc
#include <string.h>         // memcpy
#include <time.h>
#include "sorting_libs.h" 


#define MIN_ARRAY_SIZE 5 
#define MAX_ARRAY_SIZE 100
#define DEFAULT_NUM_TESTS 3ULL 


// Internal-only tracking structure
typedef struct {
    size_t index_a;
    size_t index_b;
    int val_a;
    int val_b;
} FailureInfo;


/**
 * Parses a command-line string into a size_t safely.
 * Rejects negative numbers, overflow, and invalid text.
 */
static bool parse_size_t(const char *str, size_t *out_val){
    if (str == NULL || out_val == NULL){
        return false;
    }

    // reject negative signs to prevent silent wrapping
    if(strchr(str, '-')){
        return false;
    }

    char *endptr; 

    errno = 0;
    unsigned long long parsed_val = strtoull(str, &endptr, 10);
    // 1. check for strtoull level overflow  (value > ULLONG_MAX)
    if (errno == ERANGE && parsed_val == ULLONG_MAX){
        return false;
    }

    // 2. Reject if no digits were found or trailing garbage character
    if (endptr == str || *endptr != '\0'){
        return false;
    }

    // 3. Check for size_t specific overflow (on 32-bit system where size_t)
    if (parsed_val > SIZE_MAX){
        return false;
    }

    *out_val = (size_t)parsed_val;
    return true;
}


// Checks sorting (ascending order) and records exact failure point
// Marked static to declare file-local scope
static bool verify_sorted(const int *arr, size_t n, FailureInfo *fail_info) {
    for (size_t i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if(fail_info != NULL){
                fail_info->index_a = i;
                fail_info->index_b = i+1;
                fail_info->val_a = arr[i];
                fail_info->val_b = arr[i+1];
            }
            return false;
        }
    }
    return true;
}

static void print_array(const int *arr, size_t n){
    printf("[");
    for(size_t i = 0; i < n; i++){
        printf("%d%s", arr[i], (i < n-1)? ", " : "");
    }
    printf("]\n");
}


static void fill_array_random(int *arr, size_t n){
    for(size_t i = 0; i < n; i++){
        arr[i] = rand();
    }
}


static void test_bubble_sort(const char* test_name, const int *original_arr, size_t n){

    // Allocate memory and retain a copy of the original state
    int *working_arr = malloc(n * sizeof(int));
    if (!working_arr){
        perror("Allocation failed");
        return;
    }

    memcpy(working_arr, original_arr, n * sizeof(int));

    // Execute the sorting algorithm
    bubble_sort(working_arr, n);

    // Verify results
    FailureInfo fail_info;
    if (verify_sorted(working_arr, n, &fail_info)) {
        printf("[ PASS ] %s\n", test_name);
    } else {
        printf("[ FAIL ] %s\n", test_name);
        printf(" -> Original: ");
        print_array(original_arr, n);
        printf(" -> Result:   ");
        print_array(working_arr, n);
        printf(" -> Mismatch: Index %zu (%d) > Index %zu (%d)\n",
            fail_info.index_a, fail_info.val_a, 
            fail_info.index_b, fail_info.val_b);
    }

    free(working_arr);
}

static void run_random_tests(size_t num_tests){

    printf("\n=== Running %zu Random Fuzzing Tests ---\n", num_tests);

    for(size_t i = 0; i < num_tests; i++){
        size_t n = rand() % (MAX_ARRAY_SIZE - MIN_ARRAY_SIZE + 1) + MIN_ARRAY_SIZE;

        // allocate memory safely
        int *original_arr = malloc(n * sizeof(int));
        if(!original_arr){
            perror("Allocation failed for random test generation");
            return;
        }

        fill_array_random(original_arr, n);

        // securely format string to prevent buffer overflows
        char test_name[64];
        snprintf(test_name, sizeof(test_name), "Random Test #%zu (Size: %zu)", i+1, n);

        // execute test
        test_bubble_sort(test_name, original_arr, n);

        // free memory to prevent leaks
        free(original_arr);
    }
}

static void run_tests(void){
    
    {   // Edge Case: Single Element Array
        const char *name = "Single Element Array";
        int arr[] = {1};
        test_bubble_sort(name, arr, sizeof(arr) / sizeof(arr[0]));
    }

    {   // Array already sorted
        const char *name = "Already Sorted Array";
        int arr[] = {1, 2, 3, 4, 5};
        test_bubble_sort(name, arr, sizeof(arr) / sizeof(arr[0]));
        
    }

    {   // Unsorted array
        const char *name = "Unsorted Array";
        int arr[] = {64, 34, 25, 12, 22, 11, 90};
        test_bubble_sort(name, arr, sizeof(arr) / sizeof(arr[0]));
    }
}



int main(int argc, char *argv[]) {
    srand(time(NULL));

    size_t num_random_tests = DEFAULT_NUM_TESTS;

    if (argc > 1){
        if (!parse_size_t(argv[1], &num_random_tests)){
            fprintf(stderr, "Error: Argument %s is not be a valid positive integer withing range. "
                "Using default number of tests\n", argv[1]);
        }
    }
       

    printf("\n--- Running Sorting Algorithm Tests ---\n");
    run_tests();
    run_random_tests(num_random_tests);
    printf("---------------------------------------\n");
    return 0;
}
