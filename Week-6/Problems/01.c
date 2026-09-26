#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000000

int main() {
	static long long arr[N];
    long long serial_sum = 0, parallel_sum, i;
	
	for (i = 0; i < N; i++) { 
		arr[i] = i + 1;
	}
	
    // serial sum
	double start = omp_get_wtime();

	for (i = 0; i < N; i++) { 
		serial_sum += arr[i];
	}
	
    double end = omp_get_wtime();

    printf("Serial sum = %lld\n", serial_sum);
    printf("Serial Time = %f seconds\n", end - start);

    // parallel sum using critical
    parallel_sum = 0;
    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        #pragma omp critical 
        {
            parallel_sum += arr[i];
        }
    }

    end = omp_get_wtime();

    printf("Parallel sum (Critical) = %lld\n", serial_sum);
    printf("Parallel Time (Critical) = %f seconds\n", end - start);

    return 0;
}
