#include <stdio.h>
#include <omp.h>
#define N 1000000
 
int main() {
    static int arr[N], i;

    // Serially
    double start = omp_get_wtime();

    for (i = 0; i < N; i++) {
        arr[i] = i * 2;
    }

    double end = omp_get_wtime();

    printf("Serial Array Initialization Time: %f seconds\n", end - start);

    // Parallel
    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        arr[i] = i * 2;
    }

    end = omp_get_wtime();

    printf("Parallel Array Initialization Time: %f seconds\n", end - start);

    printf("Verified arr[0] = %d, arr[100000] = %d, arr[999999] = %d\n", arr[0], arr[100000], arr[999999]);
    
    return 0;
}