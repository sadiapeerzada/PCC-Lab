#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
	int i;
	long long sum1 = 0, sum2 = 0;
	double start_1, end_1, start_2, end_2;

	// time the parallel block	
	start_1 = omp_get_wtime();
	
	#pragma omp parallel for
	for(i = 1; i <= N; i++) {
		sum1 += i;
	}
	end_1 = omp_get_wtime();
	printf("Time to perform parallel block = %f\n", end_1 - start_1);
	
	// time the serial block
	start_2 = omp_get_wtime();
	
	for(i = 1; i <= N; i++) {
		sum2 += i;
	}
	end_2 = omp_get_wtime();
	printf("Time to perform serial block = %f\n", end_2 - start_2);
}
