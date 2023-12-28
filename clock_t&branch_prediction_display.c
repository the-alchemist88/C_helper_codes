#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 500'000'000

#ifndef WCASE // check worst case scenerio(by putting the searched element last index)
#define WCASE
#else
#define QSORT // check sorted array search performance
#endif

void set_array_zero(int* p, size_t size)
{
	while (size--)
		*p++ = 0; // returns a number up to RAND_MAX
}

void randomize()
{
	srand((unsigned)time(NULL));
}

void set_array_random(int* p, size_t size)
{
	while (size--)
		*p++ = rand(); // returns a number up to RAND_MAX
}

print_array(const int* p, size_t size)
{

	for (size_t i = 0; i < size; ++i)
	{
		if (i && i % 20 == 0)
			putchar('\n');
		printf("%3d ", p[i]);
	}

	puts("\n-------------------------------------------------------------------------------------------------\n");
}

int fcmp(const void* vp1, const void* vp2)
{
	return *(const int*)vp1 - *(const int*)vp2;
}

int main()
{
	puts("Array is being prepared, please wait..\n");

	int* ptr = (int*)malloc(sizeof(int) * SIZE);

	if (!ptr)
	{
		fprintf(stderr, "cannot allocate memory\n");
		return 1;
	}

	randomize();// seed with time (seconds since epoch)
	set_array_random(ptr, SIZE);

	int ival = 0;
	size_t i;

	
#ifdef QSORT // enable sorted array test
	qsort(ptr, SIZE, sizeof(*ptr), fcmp);
	puts("Array is sorted, press enter to start the search\n");
#elif defined WCASE // enable worst case scenerio test
	set_array_zero(ptr, SIZE); 
	ptr[SIZE - 1] = 32767; 
	puts("Array is not sorted, press enter to start the search\n");
	ival = 32767;
	goto start;
#endif

	printf("Enter a number up to %u(RAND_MAX) to be searched in the array: ", RAND_MAX);
	scanf("%d", &ival);

	//event start
start:
	puts("Search has started\n...");
	clock_t start = clock(); // return tick_count(depends on system) 
	for (i = 0; i < SIZE && ptr[i] != ival; ++i) // linear search, if sorted still branch prediction optimization can be employed by processor
		; 

	//event end
	clock_t end = clock();
	printf("Search is over. Duration is %.3f second(s).\n", (clock() - (double)start) / CLOCKS_PER_SEC); // CLOCKS_PER_SEC --> standard,  CLK_TCK --> POSIX standard

	if (i < SIZE)
	{
		printf("The number found at index %zu\n", i);
		printf("ptr[%zu] = %d\n", i, ptr[i]);
	}
	else
	{
		puts("The number couldn't be found\n");
	}

	puts("Program has ended\n");

	(void)getchar();
	(void)getchar();

	print_array(ptr, SIZE); // force compiler not to do optimization, because ptr is not used

	free(ptr);

}
