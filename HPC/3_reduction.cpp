#include <iostream>
#include <omp.h>
#include <climits>

using namespace std;

int min_reduction(int arr[], int size){
	int min_val = INT_MAX;
	#pragma omp parallel for reduction(min:min_val)
	for(int i=0; i<size; i++){
		if(arr[i]<min_val){
			min_val=arr[i];
		}
	}
	return min_val;
}

int max_reduction(int arr[], int size){
	int max_val = INT_MIN;
	#pragma omp parallel for reduction(max:max_val)
	for(int i=0; i<size; i++){
		if(arr[i]>max_val){
			max_val=arr[i];
		}
	}
	return max_val;
}

int sum_reduction(int arr[], int size){
	int sum_val = 0;
	#pragma omp parallel for reduction(+:sum_val)
	for(int i=0; i<size; i++){
		sum_val+=arr[i];
	}
	return sum_val;
}

double avg_reduction(int arr[], int size){
	int sum_val = 0;
	#pragma omp parallel for reduction(+:sum_val)
	for(int i=0; i<size; i++){
		sum_val+=arr[i];
	}
	
	double avg=static_cast<double>(sum_val)/size;
	return avg;
}

int main(){
	int size;
	cout << "Enter size of array: ";
	cin >> size;
	
	int arr[size];
	cout << "Enter array elements: " << endl;
	for(int i=0; i<size; i++){
		cin >> arr[i];
	}
	
	int min = min_reduction(arr, size);
	int max = max_reduction(arr, size);
	int sum = sum_reduction(arr, size);
	double avg = avg_reduction(arr, size);

	cout << "Minimum value: " << min << endl;
	cout << "Maximum value: " << max << endl;
	cout << "Sum of elements: " << sum << endl;
	cout << "Average of elements: " << avg << endl; 

	return 0;
}





// The provided code demonstrates the use of reduction clauses in OpenMP for finding the minimum, maximum, sum, and average values of an array. Here's an explanation of the code:

// The code includes necessary libraries such as <iostream>, <omp.h>, and <climits>.

// The min_reduction function is defined, which takes an array (arr) and its size (size) as parameters. It finds the minimum value in the array using the OpenMP reduction clause with the min operator.

// Inside the min_reduction function, a variable min_val is initialized to INT_MAX, representing the maximum possible integer value. This ensures that any element in the array will be smaller than the initial min_val.

// The #pragma omp parallel for directive is used to parallelize the loop that iterates over the array.

// The reduction clause reduction(min:min_val) specifies that each thread will have its own private copy of min_val, and the final result will be the minimum value among all the private copies.

// The loop compares each element of the array with min_val and updates min_val if a smaller value is found.

// The min_val is returned as the minimum value of the array.

// Similarly, the max_reduction, sum_reduction, and avg_reduction functions are defined to find the maximum value, sum, and average of the array using reduction clauses with the max and + operators.

// The main function is defined, which is the entry point of the program.

// The user is prompted to enter the size of the array.

// An integer array arr is created with the specified size.

// The user is prompted to enter the elements of the array.

// The min_reduction, max_reduction, sum_reduction, and avg_reduction functions are called to calculate the minimum, maximum, sum, and average values of the array, respectively.

// The calculated values are printed to the console.

// The program ends with a return statement.

// Overall, the code demonstrates how to use OpenMP reduction clauses to perform parallel reductions on arrays, allowing for efficient computation of aggregate values. The reduction clauses help avoid data races and provide a concise way to perform common reduction operations in parallel.





