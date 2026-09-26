#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 2000000
 
int main() {

    static int arr[N];
    int even_count = 0, parallel_even_count = 0, i;

    srand(time(NULL));

    for (i = 0; i < N; i++) {
        arr[i] = rand();
    }

    // Serial count
    double start = omp_get_wtime();

    for (i = 0; i < N; i++) {
        if (arr[i] % 2 == 0) {
            even_count++;
        }
    }

    double end = omp_get_wtime();

    printf("Serial Even Count: %d\n", even_count);
    printf("Serial Time: %f seconds\n", end - start);


    // Parallel count Race Condition
    parallel_even_count = 0;

    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < N; i++) {

        if (arr[i] % 2 == 0) {
            parallel_even_count++;
        }
    }

    end = omp_get_wtime();

    printf("Parallel Even Count (Race Condition): %d\n", parallel_even_count);
    printf("Parallel Time: %f seconds\n", end - start);

    return 0;
}