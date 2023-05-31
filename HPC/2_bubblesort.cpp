#include <iostream>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n){
	int i, j;
	bool swapped;
	
	for(i=0; i<n-1; i++){
		swapped = false;
	
		#pragma omp parallel for shared(arr, n, swapped)
		for(j=0; j<n-i-1; j++){
			if(arr[j]>arr[j+1]){
				#pragma omp critical
				{
					swap(arr[j], arr[j+1]);
					swapped = true;
				}			
			}
		}
			
		if(!swapped){
			break;
		}	
	}
}


int main(){
	int n;
	cout << "Enter length of array: " << endl;
	cin >> n;

	int arr[n];
	cout << "Enter array elements: " << endl;
	
	for(int i=0; i<n; i++){
		cin >> arr[i];
	}
	
	bubbleSort(arr, n);
	
	cout << "Sorted array is: " << endl;
	for(int i=0; i<n; i++){
		cout << arr[i]<<" ";
	}

	return 0;
}




// The provided code is an implementation of the Bubble Sort algorithm with OpenMP parallelization. It sorts an array of integers in ascending order. Let's go through the code step by step:

// The code includes necessary libraries such as <iostream> and <omp.h>.

// The bubbleSort function is defined, which takes an array (arr) and its length (n) as parameters.

// Inside the bubbleSort function, two nested loops are used to iterate over the array and compare adjacent elements.

// A boolean variable swapped is initialized to keep track of whether any swaps have occurred in the current iteration.

// The outer loop (i) controls the number of iterations required to sort the array. It runs for n-1 iterations.

// The inner loop (j) iterates over the unsorted part of the array. The #pragma omp parallel for directive is used to parallelize this loop, allowing multiple threads to process the elements simultaneously.

// Inside the inner loop, adjacent elements are compared, and if they are in the wrong order, a swap is performed. A critical section (#pragma omp critical) is used to ensure that only one thread accesses the swap operation at a time.

// After the inner loop completes, the swapped variable is checked. If no swaps were made in the current iteration, it means the array is already sorted, and the outer loop is terminated early using the break statement.

// The main function is defined, which is the entry point of the program.

// The user is prompted to enter the length of the array (n).

// An integer array arr is created with a size of n.

// The user is prompted to enter the elements of the array.

// The bubbleSort function is called to sort the array.

// The sorted array is printed to the console.

// The program ends with a return statement.

// Overall, the code implements Bubble Sort algorithm with parallelization using OpenMP. It allows multiple threads to work on different parts of the array simultaneously, potentially speeding up the sorting process.




