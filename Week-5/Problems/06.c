#include <stdio.h>
#include <omp.h>

#define N 20

int main() {

    int arr[N], i, j;

    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        int elements = N / num_threads;

        int start = thread_id * elements;
        int end = start + elements;

        for (j = start; j < end; j++) {
            arr[j] = thread_id;
        }
    }

    printf("Final Array: ");

    for (i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}