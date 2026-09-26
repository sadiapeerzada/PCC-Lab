#include <stdio.h>
#include <omp.h>

int main() {
    int i;

    printf("Running with default threads:\n");
#pragma omp parallel for
    for (i = 0; i < 5; i++) {
        printf("Default: Iteration %d from thread %d\n", i, omp_get_thread_num());
    }
    printf("\nRunning with 2 threads:\n");
#pragma omp parallel for num_threads(2)
    for (i = 0; i < 5; i++) {
        printf("2 Threads: Iteration %d from thread %d\n", i, omp_get_thread_num());
    }
    printf("\nRunning with 8 threads (if available):\n");
#pragma omp parallel for num_threads(8)
    for (i = 0; i < 5; i++) {
        printf("8 Threads: Iteration %d from thread %d\n", i, omp_get_thread_num());
    }
    return 0;
}