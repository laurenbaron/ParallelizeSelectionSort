// C program for implementation of selection sort
#include <stdio.h>
#include <time.h>
#include "omp.h"

//create tuple for the minimum so we know the value to compare to and the index to swap with
struct min_tuple {
	int min_value; //need for the reduction clause, can't access arr[index]
	int min_index;
};

//custom reduction on each thread's minimum value (reduce each thread's min to overall min)
#pragma omp declare reduction(minimum : struct min_tuple : omp_out = omp_in.min_value < omp_out.min_value ? omp_in : omp_out)

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
	int arr[] = {64, 25, 12, 22, 11,1,3,23,4,56,788,7,65,43,2,24,7,86,5,32,2,46,7,889,9,
	1,1,345,5,76856,74,3,6,7,85,3,23,56,7,1,32,4,5,8,3,4,2,1,2,5,8,798,4,5,6,9,7,6,3,2,1,
	23,4,56,8,2,34,56,8,5,12,2,3,54,34,2,2,4,5,5,45,6,54,56,3457,35,8,3,45,6,8,7,5,4,53,
	2,2,1,2,3,4,5,6,78,90,0,9,8,7,6,5,3,2,1,4,5,7,8,9,2,34,5,432,3,45,234,5,234,52,2345,2,
	22,3,4,23,3,4,5,43,2,345,3,2,45,2,3,45,43,2,1,5,56,78,3,45,62,3,45,34,57,568,657,89,3,4,
	3,4,56,2,34,5,345,67,78,23,345,6,2346,67,58,69,467,53,654,643,57,58,69,3,6,2,534,6,674,
	2345,3,4,6,43,6,58,8,567,9,3,456,34,57,58,6579,870,98,2,452,345,3456,76,873,34,57,245,
	23,6,75,86,5,3,34567,76,3,5,56,3,1,2,3,4,57,6,8,9,9,7,6,4,3,2,1,2,4,5,7,6,5,4,3,2,3,4,7,
	1,2,3,4,5,6,7,78,9,8,7,6,23,5,5,4,3,425,2345,6347,458,34,6,53,467,7,68,23,253,56,2,3,4,5,
	1,2,23,5,2346,3457,4568,567,6,356,3457,8,8,3,3456,7,3456,5,4,3,4,5,6,7,9,7,6,4,3,23,34,4,
	2,3,5,4657456,74,3,425,56,3,9,5,23,45,7,84,64,63,6,8768,92,3,4,4,4,2,5,4,6,88,9,4,3,67,2,
	2,3,5,3,45,6,54,3,45,6,54,3,45,6,34,5,6,6,8,2,3,2,3,2,5,456,6,89,3,643,3,45,6,5,4,3,44,3,
	23,4,5,7,4,5,4,2,3,4,6,7,8,2,345,4,3,24,6,345,7,456,4,642,5,346,4,4,35,4,5,65,4,5,6,5,4,
	2,3,4,45,57,68,3,453,52,6435,7,8,5,45,6,4,34,4,4,5,6,84,2,3,4,4,5,67,2,3,4,5,435,6,5,43,
	34,5,65,43,4,56,5,43,4,56,54,3,4,56,4,3,4,56,54,3,45,6,54,3,4,56,4,3,4,56,54,3,4,56,4,34,
	34,56,5,43,4,56,54,34,5,64,3,4,5,65,4,3,4,5,6,568,769,8,9,6657,57,98,7,56,67,9876,7876,6,
	64,3,6867,9,96756,7,5,69,1,1,2,23,3,43,245,36,45,6,5,45,6,54,5,6,54,5,65,4,56,54,3,45,22,
	2,34,32,3,4,32,34,3,3,4,5,6,54,5,4,3,45,6,543,4,5,7,78,89,679,782,4764,56,4,5,6,765,4,56,
	4,4,543,6,54,3,4,5,52,45,546,47,3,534,6,34,562,879,5,4,3,4,5,43,4,5,43,45,43,4,5,23,45,3,
	34,23,4,3,2,35,6,54,6,67,5,8,67,8,6,54,5,6,54,452,3,2,34,32,2,2,3,42,34,3,2,3,54,64,57,
	3,4,54,53,4,55,6,67,65,657,46,56,4,56,6,75,8,67,2,67,4,635,34,45,2,3,4,23,4,23,4,324,23,
	2,3,43,25,436,5,66,3,78,4,4,5,6,76,5,6,76,5,3,3,45,64,34,5,43,5,34,645,6,657,658,657,4,4,
	2,34,3,4,435,4,654,765,7,68,678,6,79,87,87,54,345,43,2,34,5,3,4,56,54,3,57,68,765,8675,6,
	3,2,34,3,5,8,64,3,3,3,6,633,4,342,1,2,4,45,36,347,487,69,70,3456,2,3,4,3,1,235,3,645,7,5,
	3,45,4,32,57,657,7,789,7,3,542,3858,78,45,68,72,1,234,2,3,45,43,65,4,7645,68,7,68,67,4,5,
	122,2,3,2,42,3,4,32,34,78,5678,4,3,46,4,35,74,567,568,345,11,611,3,62,85678,54,657,46,5};
	int n = sizeof(arr)/sizeof(arr[0]);
	selectionSort(arr, n);
	printf("Sorted array: \n");
	printArray(arr, n);
	end=omp_get_wtime();
	printf("Selection sort openMP parallel code took %f seconds \n", end-begin);
	return 0;
}

