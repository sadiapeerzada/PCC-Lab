#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
 
#define N 1000000

int main() {
    static int arr[N];
    int min_value, i;

    srand(time(NULL));

    for (i = 0; i < N; i++) {
        arr[i] = rand() % 1000000 + 1;
    }

    min_value = arr[0];

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }

    printf("Array Min Value (Parallel, potentially incorrect): %d\n", min_value);

    return 0;
}