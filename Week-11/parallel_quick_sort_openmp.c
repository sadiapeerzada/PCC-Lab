// Partially Solved Problem 11.1: Parallel Quick Sort (OpenMP)
// Aligarh Muslim University, Lab V, Week 11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#define N 100000
#define THRESHOLD 1024
static int cmp(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y)-(x < y);
}
static int partition(int *a, int lo, int hi) {
    int pivot = a[hi], i = lo;
    for (int j = lo; j < hi; j++) {
        if (a[j] <= pivot) {
            int t = a[i]; a[i] = a[j]; a[j] = t;
            i++;
        }
    }
    int t = a[i]; a[i] = a[hi]; a[hi] = t;
    return i;
}
static void quicksort_task(int *a, int lo, int hi) {
    if (hi <= lo) return;
    if (hi-lo+1 <= THRESHOLD) {
        qsort(a+lo, (size_t)(hi-lo+1), sizeof(int), cmp);
        return;
    }
    int p = partition(a, lo, hi);
    #pragma omp task shared(a) firstprivate(lo,p)
    quicksort_task(a, lo, p-1);
    #pragma omp task shared(a) firstprivate(hi,p)
    quicksort_task(a, p+1, hi);
    #pragma omp taskwait
}
static void parallel_quicksort(int *a, int n, int threads) {
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp single
        quicksort_task(a, 0, n-1);
    }
}
int main(void) {
    int *original = malloc((size_t)N*sizeof(int));
    int *a = malloc((size_t)N*sizeof(int));
    int *reference = malloc((size_t)N*sizeof(int));
    if (!original || !a || !reference) return 1;
    srand(2026);
    for (int i = 0; i < N; i++) original[i] = rand();
    memcpy(reference, original, (size_t)N*sizeof(int));
    double t = omp_get_wtime();
    qsort(reference, N, sizeof(int), cmp);
    double serial = omp_get_wtime()-t;
    printf("Sequential qsort: %.6f s\n", serial);
    int thread_counts[] = {1,2,4};
    for (int k = 0; k < 3; k++) {
        int p = thread_counts[k];
        memcpy(a, original, (size_t)N*sizeof(int));
        t = omp_get_wtime();
        parallel_quicksort(a, N, p);
        double elapsed = omp_get_wtime()-t;
        double speedup = elapsed > 0 ? serial/elapsed : 0;
        printf("Threads=%d time=%.6f speedup=%.3f efficiency=%.3f %s\n",
               p, elapsed, speedup, speedup/p,
               memcmp(a, reference, (size_t)N*sizeof(int)) == 0 ? "SORTED":"ERROR");
    }
    free(original); free(a); free(reference);
    return 0;
}
