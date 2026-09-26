#include <stdio.h>
#include <omp.h>

int main() {
    printf("Maximum threads available: %d\n", omp_get_max_threads());
    printf("Number of processors: %d\n", omp_get_num_procs());

    #pragma omp parallel
    {
        printf("Inside parallel region: Thread %d\n", omp_get_thread_num());
    }
    return 0;
}
