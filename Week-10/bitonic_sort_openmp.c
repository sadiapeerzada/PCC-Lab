// Solved Problem 10.1: Parallel Bitonic Sort (OpenMP)
// Aligarh Muslim University, Lab V, Week 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}
static void bitonic_sort(int *a, int n, int threads) {
    for (int k = 2; k <= n; k *= 2) {
        for (int j = k / 2; j > 0; j /= 2) {
            #pragma omp parallel for num_threads(threads) schedule(static)
            for (int i = 0; i < n; i++) {
                int partner = i ^ j;
                if (partner > i) {
                    int ascending = ((i & k) == 0);
                    if ((ascending && a[i] > a[partner]) ||
                        (!ascending && a[i] < a[partner])) {
                        int tmp = a[i];
                        a[i] = a[partner];
                        a[partner] = tmp;
                    }
                }
            }
        }
    }
}
int main(void) {
    int sizes[] = {1024, 4096, 16384};
    int threads[] = {1, 2, 4};
    for (int z = 0; z < 3; z++) {
        int n = sizes[z];
        int *original = malloc((size_t)n * sizeof(int));
        int *baseline = malloc((size_t)n * sizeof(int));
        int *work = malloc((size_t)n * sizeof(int));
        if (!original || !baseline || !work) return 1;
        srand(100 + n);
        for (int i = 0; i < n; i++) original[i] = rand() % 10000;
        memcpy(baseline, original, (size_t)n * sizeof(int));
        double t = omp_get_wtime();
        qsort(baseline, n, sizeof(int), cmp_int);
        double serial_time = omp_get_wtime() - t;
        printf("N=%d qsort time=%.6f s\n", n, serial_time);
        for (int p = 0; p < 3; p++) {
            memcpy(work, original, (size_t)n * sizeof(int));
            t = omp_get_wtime();
            bitonic_sort(work, n, threads[p]);
            double parallel_time = omp_get_wtime() - t;
            int correct = memcmp(work, baseline, (size_t)n*sizeof(int)) == 0;
            double speedup = parallel_time > 0 ? serial_time/parallel_time : 0;
            printf("  Threads=%d time=%.6f speedup=%.3f efficiency=%.3f %s\n",
                threads[p], parallel_time, speedup, speedup/threads[p],
                correct ? "SORTED" : "ERROR");
        }
        free(original); free(baseline); free(work);
    }
    return 0;
}
