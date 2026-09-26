#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define N 1000000
 
int main() {
    static int arr[N];
    int max_value, i;

    srand(time(NULL));

    for(i = 0; i < N; i++) {
        arr[i] = rand() % 1000000;
    }

    // serial
    max_value = arr[0];
    double start = omp_get_wtime();

    for (i = 1; i < N; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    double end = omp_get_wtime();

    printf("Max Value (serial): %d\n", max_value);
    printf("Serial Time: %f seconds\n", end - start);

    // locked parallel
    max_value = arr[0];

    omp_lock_t lock;
    omp_init_lock(&lock);

    start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        omp_set_lock(&lock);

        if (arr[i] > max_value) {
            max_value = arr[i];
        }

        omp_unset_lock(&lock);
    }

    end = omp_get_wtime();

    printf("Max Value (locked parallel): %d\n", max_value);
    printf("Parallel Time: %f seconds\n", end - start);

    return 0;
}