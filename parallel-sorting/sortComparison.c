#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include "omp.h"

#include "difSort.h"


int lenArr = 100000000; // 262144000 = 1000 MBytes = 1 GByte
int numthreads = 16;



void quickSort(int* arr, int left, int right) 
{
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];

  	/* PARTITION PART */
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}

	/* RECURSION PART */
	if (left < j){ quickSort(arr, left, j);  }
	if (i< right){ quickSort(arr, i, right); }
}





// Comparator used in qsort()
int cmpfunc (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}



int main(){
	int minMum = 1;
	int maxNum = lenArr;
	int maxNumbersDisplayed = 30;

	double startTime, stopTime;

	int* arr1;
	int* arr2; 
	int* arr3;
	arr1 = (int*) malloc(lenArr*sizeof(int));
	arr2 = (int*) malloc(lenArr*sizeof(int));
	arr3 = (int*) malloc(lenArr*sizeof(int));
	

	//printf("--------------------------------------------------");
	//printf("Info about the program: \n");
	//printf("Datatype of the array: %p", typeof() );
	//printf("Positions in the array: %d", typeof(arr1) );
	printf("\nSize of the array (aprox.): %lu MBytes \n", (lenArr*sizeof(int)/(1024*1024)) );
	printf("TOTAL MEMORY ALLOCATED:  3 x array = (aprox.): %lu MBytes \n\n", (lenArr*sizeof(int)/(1024*1024))*3 );  
	//printf("-------------------------------------------------- \n\n");


	
	// Initialise the array with random numbers
	int i;
	srand(5); // seed
	printf("Initializing the arrays with random numbers...\n");
	for (i=0; i<lenArr; i++){
		// RAND_MAX = 2147483647 = INT_MAX 
		// printf("RAND_MAX %u \n", RAND_MAX );
		arr1[i] = minMum+(rand()%maxNum);
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
		//printf("%d \n", arr1[i] ); 
	}
	printf("Initialization complete\n");



	
	if( lenArr <= maxNumbersDisplayed ){
		printf("\n\nArray BEFORE sorting: \n");
		for( i = 0 ; i < lenArr; i++ ) 
		{
			printf("%d ", arr1[i]);
		}
		printf("\n\n\n");
	}


	printf("\nSorting with sequential QuickSort.."); fflush(stdout);
	startTime=omp_get_wtime();
	quickSort(arr2, 0, lenArr-1);
	stopTime = omp_get_wtime();

	printf("\nSorted sequential in (aprox.): %f seconds \n\n", (stopTime-startTime));

	int ok1 = 1;
	int l1;
	for(l1 = 0; l1 < lenArr-1 && ok1; l1++) {
		if(arr2[l1]>arr2[l1+1]) {ok1 = 0; printf("SORTING SEQUENTIAL ERROR\n"); break;}
	}
	if(ok1)
		printf("SORTING SEQUENTIAL OK\n");

	printf("\nSorting with custom PARALLEL QuickSort... "); fflush(stdout);
	startTime = omp_get_wtime();
	quickSort_parallel(arr3, lenArr, numthreads);
	stopTime = omp_get_wtime();

	printf("\nSorted parallel in (aprox.): %f seconds \n\n", (stopTime-startTime));


	int ok = 1;
	int l;
	for(l = 0; l < lenArr-1 && ok; l++) {
		if(arr3[l]>arr3[l+1]) {ok = 0; printf("SORTING PARALLEL ERROR\n"); break;}
	}
	if(ok)
		printf("SORTING PARALLEL OK\n");



	printf("\n\n");

	free(arr1);
	free(arr2);
	free(arr3);

	return 0;
}
