# Bubble Sort

The Bubble Sort algorithm in computer science is a basic sorting technique for sorting lists (arrays) in a specific order, ascending or descending. It wors by repeatedly swapping adjacent element if they are in the incorrect order. The process repeats until the entire list is sorted.

It is named bubble sort after the way the elment move to their correct position in the list. In each iteration, the largest (or smallest, depending on the sorting order) element rises to its correct position. The process is similar to bubbles rising to the surface of water.


## How Bubble Sort Works (Ascending Order)

1. Start at the beginning of the list.
2. Compare the first two elements. If the first element is greater than the second element, swap them.
3. Move to the next pair of elements, compare, and swap if necessary.
4. Continue this process until the end of the list. (The largest unsorted number will naturally "bubble" up to its correct position at the end).
5. Repeat the entire process for the remaining unsorted elements.
6. Stop when a full pass completes without making any swaps.


## Pseudocode (Ascending Order)

```text
procedure bubbleSort(array A, integer n)
    // n is the number of elements in array A
    
    // Perform up to n passes through the array
    for i = 0 to n - 1
        swapped = false
        
        // Compare adjacent elements
        for j = 0 to n - i - 2
            if A[j] > A[j + 1] then
                // Swap them if they are in the wrong order
                swap(A[j], A[j + 1])
                swapped = true
            end if
        end for
        
        // If no two elements were swapped in this pass, the list is sorted
        if not swapped then
            break
        end if
    end for
end procedure

```

## Example 

Credit for this example belongs to W3 Schools, https://www.w3schools.in/data-structures/sorting-techniques/bubble-sort-algorithm

Let's assume you have an unsorted array [5, 3, 8, 2, 1] and want to sort it into ascending order. 

| Pass | Comparisons and Actions | Resulting Array |
| --- | --- | --- |
| 1 | Compare 5 and 3, swap | [ 3, 5, 8, 2, 1] |
| 1 | Compare 5 and 8, no swap | [ 3, 5, 8, 2, 1] |
| 1 | Compare 8 and 2, swap | [3, 5, 2, 8, 1] | 
| 1 | Compare 8 and 1, swap | [3, 5, 2, 1, 8] |

After the first pass, the largest numer (8) has "bubbled up" to its correct position at the end of the array.

| Pass | Comparisons and Actions | Resulting Array |
| --- | --- | --- |
| 2 | Compare 3 and 5, no swap | [ 3, 5, 2, 1, 8] |
| 2 | Compare 5 and 2, swap | [ 3, 2, 5, 1, 8] |
| 2 | Compare 5 and 1, swap | [ 3, 2, 1, 5, 8] |

After the second pass, the next largest number (5) is now in its correct position, before the already sorted (8).

| Pass | Comparisons and Actions | Resulting Array |
| --- | --- | --- |
| 3 | Compare 3 and 2, swap | [ 2, 3, 1, 5, 8] |
| 3 | Compare 3 and 1, swap | [ 2, 1, 3, 5, 8] |

After the third pass, the number (3) is in its correct position.


| Pass | Comparisons and Actions | Resulting Array |
| --- | --- | --- |
| 4 | Compare 2 and 1, swap | [ 1, 3, 3, 5, 8] |

After the fourth pass, all element are now in their correct positions, and the array is sorted in ascending order.


## Algorithm Complexity

### Time Complexity

- Worst-Case Time Complexity: O(n^2)
    - Occurs when the input array is sorted in reverse order 
    - The algorithm must perform (n-1) passes, making the nested loops compare and swap every single adjacent pair.
- Average-Case Time Complexity: O(n^2)
    - Occurs when elments are in a random, arbitrary order.
    - The algorithm still executes O(n^2) total comparisons on average to move items to correct spots.
- Best-Case Time Complexity: O(n)
    - Occurs when the input array is already completely sorted.
    - **Note**: This linear time complexity is only achieved using an *optimized* version of bubble sort. This version tracks if any swaps occurred during a pass using a boolean flag. If no elements are swapped during the first pass, the algorithm terminates early after n-1 comparison.


### Space Complexity 

- Auxiliary Space Complexity: O(1)
    - Bubble sore is an in-places sorting algorithm.
    - It rearranges elements directly within the original array.
    - It requires only a fixed, constant amount of addtional memory for loop counters and a single temporary swap variable.

### Stability 

- Stable
    - An algorithm is stable if it preserves the relative order of identical elements.
    - Bubble sore checks if the left elements is strictly greater than the right element (array[j] < array[j+1]) before swapping.
    - Because equal elements do not trigger a swap, their original relative positioning reamins unchanged.
