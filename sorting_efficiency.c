#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE
#include <time.h>   // clock_t


void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print_arr(const int* p, size_t n)
{
	while (n--)
		printf("%d ", *p++);
	putchar('\n');
}

int* alloc_and_set_arr_rand(size_t length)
{
	int* arr = (int*)malloc(sizeof(int) * length);
	if (!arr)
	{
		fprintf(stderr, "cannot obtain memory for array\n");
		exit(EXIT_FAILURE);
	}

	srand((unsigned)time(NULL));
	
	for (size_t i = 0; i < length; ++i)
		arr[i] = rand();

	return arr;
}

void Qsort(int* const number, int first, int last) // standalone qsort
{
	int i, j, pivot;
	if (first < last) 
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (number[i] <= number[pivot] && i < last)
				i++;
			while (number[j] > number[pivot])
				j--;
			if (i < j) {
				swap(&number[j], &number[i]);

			}
		}
		swap(&number[j], &number[pivot]);
		Qsort(number, first, j - 1);
		Qsort(number, j + 1, last);
	}
}

int partition(int* arr, int low, int high) // auxiliary func of quicksort func
{
	int pivot = low; // assumed first element as pivot
	int i = low; 
	int j = high;

	while (i < j)
	{
		while (arr[i] <= arr[pivot] && i < high)
			++i;
			
		while (arr[j] > arr[pivot])
			--j;

		if (i < j)
		swap(&arr[i], &arr[j]);
	}
	swap(&arr[j], &arr[pivot]);

	return j;
}

void quicksort(int* arr, int low, int high) // used with partition func
{
	if (low < high)
	{
		int j = partition(arr, low, high);
		quicksort(arr, low, j - 1);
		quicksort(arr, j + 1, high);
	}
	
}

void bubble_sort(int* arr, size_t n)
{
	int traverse = 0;
	int temp = 0;
	
	for (size_t i = 1; i < n ; ++i)
	{
		for (size_t j = 0; j < n - i; ++j)
		{
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
		}
	}
}

#define SIZE 100'000

int main()
{

	// Test code for checking sorting functions 

	/*
	int a[] = { 17, 13, 2, 8, 3, 21, 6, 23, 19, 55, 14, 7 };
	int n = sizeof(a) / sizeof(*a);
	puts("Unsorted array: ");
	print_arr(a, n);
	bubble_sort(a, n - 1);
	//Qsort(a, 0, n - 1);
	//quicksort(a, 0, n - 1);
	puts("Sorted array: ");
	print_arr(a, n);
	*/
	
	// Test code for checking efficiency
	
    int* a = alloc_and_set_arr_rand(SIZE);

	puts("sorting has started, please wait until it is completed..\n");
	clock_t start = clock();
	bubble_sort(a, SIZE - 1); // SIZE 100'000 takes approximately 20-30 sec for bubble_sort(O(n*n)) to sort the array
	//Qsort(a, 0, SIZE - 1); // SIZE 100'000 takes approximately 0.015 sec for Qsort(O(n*log(n))) to sort the array
	//quicksort(a, 0, SIZE - 1);
	printf("end time = %.4f\n", (double)(clock() - start) / CLOCKS_PER_SEC);

	(void)getchar();
	puts("sorted array:\n"); 
	print_arr(a, SIZE); // this expression is used in order to force compiler not to do optimization based on as-if rule

	free(a);
}
