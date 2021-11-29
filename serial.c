// C program for implementation of selection sort
#include <stdio.h>
#include <time.h>
#include "omp.h"

//create tuple for the minimum so we know the value to compare to and the index to swap with
struct min_tuple {
	int min_value; //need for the reduction clause, can't access arr[index]
	int min_index;
};

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void printArray(int arr[], int size);
void selectionSort(int arr[], int n)
{
	int i, j;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array
		//use tuple 
		struct min_tuple min;
		min.min_index = i;
                min.min_value=arr[i];
		//by the end of the inner loop, min tuple will have the true minimum from the reduction 
		for (j = i+1; j < n; j++){
			//var can't appear in more than one clause so can't use first private to initialize min (min before loop is ignored)
			if(i==0 && j==1) {
				min.min_index = i;
				min.min_value=arr[i];
			}
			if (arr[j] < min.min_value) {
				min.min_index = j;
				min.min_value=arr[j];
			}
		}

		// Swap the found minimum element with the first element
		swap(&arr[min.min_index], &arr[i]);
	}
}

/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

// Driver program to test above functions
int main()
{
	double begin,end;
	begin=omp_get_wtime();
	//really big array...inefficient with serial code
	int arr[] = {};
	int n = sizeof(arr)/sizeof(arr[0]);
	selectionSort(arr, n);
	printf("Sorted array: \n");
	printArray(arr, n);
	end=omp_get_wtime();
	printf("Selection sort serial code took %f seconds \n", end-begin);
	return 0;
}

