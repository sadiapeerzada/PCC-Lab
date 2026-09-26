#include <stdio.h>
#include <omp.h>
#define N 500000
 
int main() {
    static double A[N], B[N], C[N];
    int i;

    for (i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i * 0.5;
    }

    // Serial
    double start = omp_get_wtime();

    for (i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    double end = omp_get_wtime();

    printf("Serial Element-wise Addition Time: %f seconds\n", end - start);

    // Parallel
    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    end = omp_get_wtime();

    printf("Parallel Element-wise Addition Time: %f seconds\n", end - start);
    
    return 0;
}