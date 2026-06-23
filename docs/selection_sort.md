# Selection Sort

Selection Sort is an in-place comparison sorting algorithm that repeatedly finds the minimum or maximum element from an unsorted portion of an array and moves it to the beginning. It continously splits the array conceptually into a sorted section at the front and an unsorted section at the back. The minimum element is found when sorting into ascending order and the maximum element is found for descending order.


## How Selection Sort Works (Ascending Order)

1. Start at the beginning of the list.
2. Compare the first two elements. If the first element is greater than the second element, swap them.
3. Move to the next pair of elements, compare, and swap if necessary.
4. Continue this process until the end of the list. (The largest unsorted number will naturally "bubble" up to its correct position at the end).
5. Repeat the entire process for the remaining unsorted elements.
6. Stop when a full pass completes without making any swaps.


## Pseudocode 

```text
procedure selectionSort(array A, integer n)
    // n is the number of elements in the array
    for i = 0 to n - 2
        // assume the first unsorted element is the minimum 
        minIndex = i 

        // Scan the rest of the unsorted array to find the true minimum
        for j = i + 1 to n - 1 
            if A[j] < A[minIndex]
                minIndex = j  
            end if 
        end for
        
        if minIndex != i 
            swap(A[i], A[minIndex])
        end if
    end for
end procedure

```

## Step-by-Step Example 

Assume you have an unsorted array [29, 10, 14, 37, 13] and want to sort it into ascending order. 

1. First Pass:
    1. Scan the entire array to find the smallest number (10).
    2. Swap 10 with the first element (29).
    3. Result: [ 10 | 29, 14, 37, 13] (where | marks the sorted boundary).

2. Second Pass:
    1. Scan the unsorted part [29, 14, 37, 13] to find the smallest number 13.
    2. Swap 13 with the first unsorted element (29).
    3. Result: [ 10, 13 | 14, 37, 29]

3. Third Pass:
    1. Scan the unsorted part [14, 37, 29] to find the smallest number 14.
    2. Since 14 is already at the front of this unsorted group, no physical swap changes its place.
    3. Result: [ 10, 13, 14 | 37, 29]

4. Fourth Pass:
    1. Scan [37, 29]. The smallest is 29.
    2. Swap 29 with 37.
    3. Result: [ 10, 13, 14, 29, | 37]
    4. The final element 37 is left in place as the array is sorted.


## Algorithm Complexity

- **Time Complexity**: O(n^2) for best, average, and worst-case scenarios. This happens because the nested loops execute full regardless of the initial order of the data.

- **Space Complexity**: O(1) auxiliary space. It is highly memory efficient because it sorts directly "in-place" without cloning the dataset.

- **Stability**: Unstable. Long-distance swaps can inadvertently scramble the relative order of identical keys.

