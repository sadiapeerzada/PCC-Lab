#include <stdio.h>
#include <omp.h>

#define N 1000000
 
int main() {
    static double A[N], B[N];

    double serial_dot = 0.0, parallel_dot = 0.0, start, end;
    int i;

    for (i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i * 0.5;
    }

    // Serial
    start = omp_get_wtime();

    for (i = 0; i < N; i++) {
        serial_dot += A[i] * B[i];
    }

    end = omp_get_wtime();

    printf("Serial Dot Product: %lf\n", serial_dot);
    printf("Serial Time: %f seconds\n", end - start);

    // Parallel
    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        parallel_dot += A[i] * B[i];
    }

    end = omp_get_wtime();

    printf("Parallel Dot Product (Race Condition): %lf\n", serial_dot);
    printf("Parallel Time: %f seconds\n", end - start);

    return 0;
}