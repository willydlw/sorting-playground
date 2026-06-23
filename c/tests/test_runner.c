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

// Define a function pointer type for the sorting algorithms 
typedef void (*sort_func_t)(int *, size_t);

// Structure to pair an algorithm's name with its function pointer 
typedef struct {
    const char* name;
    sort_func_t function;
} SortAlgorithm;

// Register algorithms 
static const SortAlgorithm ALGORITHMS[] = {
    {"Bubble Sort", bubble_sort},
    {"Selection Sort", selection_sort}
};
static const size_t NUM_ALGORITHMS = sizeof(ALGORITHMS) / sizeof(ALGORITHMS[0]);


// Failure data tracking structure
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


// Checks sorting (ascending order) and records exact failure point (if any)
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


// Generates an array where every element is identical
static void fill_array_uniform(int *arr, size_t n){
    for(size_t i = 0; i < n; i++){
        arr[i] = 42;
    }
}

// Generates an alredy sorted dataset
// Useful for testing best-case optimation 
static void fill_array_sorted(int *arr, size_t n){
    for(size_t i = 0; i < n; i++){
        arr[i] = (int)i;
    }
}

// Generate a worst-case dataset for algorithms like bubble and selection sort
static void fill_array_reversed(int *arr, size_t n){
    for(size_t i = 0; i < n; i++){
        arr[i] = (int)(n-i);
    }
}

static void fill_array_random(int *arr, size_t n){
    for(size_t i = 0; i < n; i++){
        arr[i] = rand();
    }
}

/**
 * Generates a nearly-sorted dataset.
 * 
 * @param arr        Pointer to the array buffer.
 * @param n          Total size of the array.
 * @param swap_pct   Percentage of elements to displace (e.g., 5 for 5%, 10 for 10%).
 */
static void fill_array_nearly_sorted(int *arr, size_t n, unsigned int swap_pct) {
    // 1. Fill the array in perfect ascending order
    for (size_t i = 0; i < n; i++) {
        arr[i] = (int)i;
    }

    if (swap_pct == 0 || n < 2) {
        return; 
    }

    // 2. Calculate target elements to disrupt (n * pct / 100)
    size_t target_elements = (n * swap_pct) / 100;

    // 3. Convert target elements to swaps by dividing by 2.
    // We add 1 before dividing by 2 to achieve standard round-to-nearest integer division.
    size_t total_swaps = (target_elements + 1) / 2;

    // 4. Execute the targeted number of random swaps
    for (size_t k = 0; k < total_swaps; k++) {
        size_t idx_a = rand() % n;
        size_t idx_b = rand() % n;

        // Ensure we actually swap different positions
        while (idx_a == idx_b) {
            idx_b = rand() % n;
        }

        int temp = arr[idx_a];
        arr[idx_a] = arr[idx_b];
        arr[idx_b] = temp;
    }
}


// Accepts a single algorithm context along with the data set 
static void test_single_algorithm(
    const SortAlgorithm *alg, 
    const char* test_name, 
    const int *original_arr, 
    size_t n){
    
        // Allocate memory and retain a copy of the original state
    int *working_arr = malloc(n * sizeof(int));
    if (!working_arr){
        perror("Allocation failed");
        return;
    }
    memcpy(working_arr, original_arr, n * sizeof(int));

    // Execute the specific sorting algorithm function pointer
    alg->function(working_arr, n);

    // Verify results
    FailureInfo fail_info;
    if (verify_sorted(working_arr, n, &fail_info)) {
        printf("[ PASS ] [%-16s] %s\n", alg->name, test_name);
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

static void evaluate_dataset(const char *test_name, const int *original_arr, size_t n){
    for(size_t i = 0; i < NUM_ALGORITHMS; i++){
        test_single_algorithm(&ALGORITHMS[i], test_name, original_arr, n);
    }
    printf("\n");
}


static void run_stress_tests(size_t size){
    printf("=== Running Performance Stress Tests (Array Size: %zu) ===\n", size);
    int *original_arr = malloc(size * sizeof(int));
    if(!original_arr){
        perror("Allocation failed for stress test generation");
        return;
    }

    // --- Scenario A: Worst Case (Completely Reversed) ---
    fill_array_reversed(original_arr, size);
    evaluate_dataset("Stress Test: Reversed Array (Worst Case)", original_arr, size);

    // --- Best Case (Already Sorted) --- 
    fill_array_sorted(original_arr, size);
    evaluate_dataset("Stress Test: Already Sorted Array (Best Case)", original_arr, size);

    // --- Nearly Sorted ---
    // Test a realistic 5% displacement scenario
    unsigned int disruption_percent = 5;
    fill_array_nearly_sorted(original_arr, size, disruption_percent);
    
    char test_label[64];
    snprintf(test_label, sizeof(test_label), "Nearly Sorted Array (%u%% Swapped)", disruption_percent);
    
    evaluate_dataset(test_label, original_arr, size);

    // --- Uniform Value --- 
    // Verifies that loop boundary conditions (like > vs >=) do not accidentally trigger
    // endless swaps on identical values
    fill_array_uniform(original_arr, size);
    evaluate_dataset("Stress Test: Uniform Value Array (Worst Case)", original_arr, size);

    free(original_arr);
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
        evaluate_dataset(test_name, original_arr, n);

        // free memory to prevent leaks
        free(original_arr);
    }
}

static void run_static_tests(void){
    printf("=== Running Static Edge Cases ===\n");
    {   // Edge Case: Single Element Array
        const char *name = "Single Element Array";
        int arr[] = {1};
        evaluate_dataset(name, arr, sizeof(arr) / sizeof(arr[0]));
    }

    {   // Array already sorted
        const char *name = "Already Sorted Array";
        int arr[] = {1, 2, 3, 4, 5};
        evaluate_dataset(name, arr, sizeof(arr) / sizeof(arr[0]));
        
    }

    {   // Unsorted array
        const char *name = "Unsorted Array";
        int arr[] = {64, 34, 25, 12, 22, 11, 90};
        evaluate_dataset(name, arr, sizeof(arr) / sizeof(arr[0]));
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
       
    printf("\n--- Running Sorting Algorithm Tests ---\n\n");
    run_static_tests();
    run_random_tests(num_random_tests);
    run_stress_tests(100);
    printf("---------------------------------------\n\n");
    return 0;
}
