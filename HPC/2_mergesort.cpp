#include <iostream>
#include <omp.h>

using namespace std;

void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < leftSize) {
        arr[k++] = left[i++];
    }
    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

void mergeSort(int arr[], int size) {
    if (size <= 1) {
        return;
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // Copying elements to the left half
            for (int i = 0; i < mid; i++) {
                left[i] = arr[i];
            }
            // Sorting the left half in parallel
            mergeSort(left, mid);
        }

        #pragma omp section
        {
            // Copying elements to the right half
            for (int i = mid; i < size; i++) {
                right[i - mid] = arr[i];
            }
            // Sorting the right half in parallel
            mergeSort(right, size - mid);
        }
    }

    merge(arr, left, mid, right, size - mid);
}

int main() {
    int size;
    cout << "Enter length of the array: ";
    cin >> size;

    int arr[size];
    cout << "Enter array elements: " << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    mergeSort(arr, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}



// The provided code is an implementation of the Merge Sort algorithm with OpenMP parallelization. It sorts an array of integers in ascending order. Let's go through the code step by step:

// The code includes necessary libraries such as <iostream> and <omp.h>.

// The merge function is defined, which takes two sorted subarrays (left and right) and their sizes (leftSize and rightSize) as parameters. This function merges the two subarrays into a single sorted array.

// Inside the merge function, three variables (i, j, and k) are initialized to keep track of the indices of the elements in the subarrays and the merged array.

// A while loop is used to compare elements from both subarrays and merge them into the arr array based on their values.

// After merging the common elements from both subarrays, if any elements are remaining in either subarray, they are copied to the arr array.

// The mergeSort function is defined, which takes an array (arr) and its size (size) as parameters. This function performs the merge sort algorithm.

// Inside the mergeSort function, a base case is defined to terminate the recursion. If the size of the array is less than or equal to 1, it is considered already sorted, and the function returns.

// The mid-point of the array is calculated to divide it into two halves.

// Two separate arrays (left and right) are created to hold the left and right halves of the original array.

// The #pragma omp parallel sections directive is used to parallelize the sorting of the left and right halves.

// Inside each section, the respective elements are copied from the original array to the left and right arrays.

// Each section then calls the mergeSort function recursively to sort its respective half.

// After the parallel sections, the merge function is called to merge the sorted left and right halves into the arr array.

// The main function is defined, which is the entry point of the program.

// The user is prompted to enter the length of the array.

// An integer array arr is created with the specified size.

// The user is prompted to enter the elements of the array.

// The mergeSort function is called to sort the array.

// The sorted array is printed to the console.

// The program ends with a return statement.

// Overall, the code implements Merge Sort algorithm with parallelization using OpenMP. It divides the array into smaller halves recursively and then merges them back together in a sorted manner. The parallel sections allow the left and right halves to be sorted concurrently, potentially improving the performance of the sorting algorithm.





