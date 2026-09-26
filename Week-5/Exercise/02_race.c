#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define ARRAY_SIZE 1000000

int main() {
	long long * arr = (long long *)malloc(sizeof(long long) * ARRAY_SIZE);
	long long serial_sum = 0;
	long long parallel_sum = 0;
	double start_time, end_time;
	int i;
	
	// Initialize array
	for (i = 0; i < ARRAY_SIZE; i++) {
		arr[i] = i + 1;
	}
	//--- Serial Summation---
	start_time = omp_get_wtime();
	
	for (i = 0; i < ARRAY_SIZE; i++){
		serial_sum += arr[i];
	}
	
	end_time = omp_get_wtime();
	printf("Serial Sum: %lld\n",serial_sum);
	printf("Serial Time: %f seconds\n",end_time-start_time);
	
	//---Parallel Summation (with intended race condition)---
	start_time = omp_get_wtime();
	
	#pragma omp parallel for
	for (i = 0; i < ARRAY_SIZE; i++){
		parallel_sum += arr[i]; // Race condition here!
	}
	end_time = omp_get_wtime();
	printf("Parallel Sum: %lld (might be incorrect due to race condition)\n", parallel_sum);
	printf("Parallel Time: %f seconds\n",end_time-start_time);
	free(arr);
	
	return 0;
}
