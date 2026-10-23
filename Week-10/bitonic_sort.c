#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

/* dir = 1 ascending, dir = 0 descending */
static void compare_and_swap(int *arr, int i, int j, int dir) {
    if ((dir && arr[i] > arr[j]) || (!dir && arr[i] < arr[j])) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

/*
 * Iterative bitonic sorting network.
 * All threads encounter every omp-for in the same order. The implicit barrier
 * at the end of each stage ensures a stage completes before the next begins.
 */
static void parallel_bitonic_sort(int *arr, int n, int threads) {
    omp_set_num_threads(threads);
    #pragma omp parallel shared(arr, n)
    {
        for (int k = 2; k <= n; k <<= 1) {
            for (int j = k >> 1; j > 0; j >>= 1) {
                #pragma omp for schedule(runtime)
                for (int i = 0; i < n; ++i) {
                    int partner = i ^ j;
                    if (partner > i) {
                        int ascending = ((i & k) == 0);
                        compare_and_swap(arr, i, partner, ascending);
                    }
                }
            }
        }
    }
}

static int compare_qsort(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

static int is_sorted(const int *a, int n) {
    for (int i = 1; i < n; ++i) if (a[i - 1] > a[i]) return 0;
    return 1;
}

static int arrays_equal(const int *a, const int *b, int n) {
    for (int i = 0; i < n; ++i) if (a[i] != b[i]) return 0;
    return 1;
}

int main(void) {
    const int sizes[] = {1024, 4096, 16384, 65536};
    const int thread_counts[] = {1, 2, 4};
    const int ns = (int)(sizeof sizes / sizeof sizes[0]);
    const int nt = (int)(sizeof thread_counts / sizeof thread_counts[0]);

    srand((unsigned)time(NULL));
    puts("Week 10: OpenMP Parallel Bitonic Sort");
    puts("Schedule: runtime (try OMP_SCHEDULE=static, OMP_SCHEDULE=dynamic,1, OMP_SCHEDULE=guided)");

    for (int s = 0; s < ns; ++s) {
        int n = sizes[s];
        int *original = malloc((size_t)n * sizeof *original);
        int *reference = malloc((size_t)n * sizeof *reference);
        int *work = malloc((size_t)n * sizeof *work);
        if (!original || !reference || !work) {
            fprintf(stderr, "Allocation failed for N=%d\n", n);
            free(original); free(reference); free(work);
            return 1;
        }

        for (int i = 0; i < n; ++i) original[i] = rand() % 100000;
        for (int i = 0; i < n; ++i) reference[i] = original[i];

        double t0 = omp_get_wtime();
        qsort(reference, (size_t)n, sizeof *reference, compare_qsort);
        double qsort_time = omp_get_wtime() - t0;
        printf("\nN = %d | qsort = %.6f s\n", n, qsort_time);

        double one_thread_bitonic = 0.0;
        for (int t = 0; t < nt; ++t) {
            int threads = thread_counts[t];
            for (int i = 0; i < n; ++i) work[i] = original[i];

            t0 = omp_get_wtime();
            parallel_bitonic_sort(work, n, threads);
            double elapsed = omp_get_wtime() - t0;
            if (threads == 1) one_thread_bitonic = elapsed;

            double speedup = threads == 1 ? 1.0 :
                (elapsed > 0.0 ? one_thread_bitonic / elapsed : 0.0);
            double efficiency = speedup / threads;

            printf("Bitonic threads=%d time=%.6f s sorted=%s matches_qsort=%s "
                   "speedup_vs_1_thread=%.3f efficiency=%.3f\n",
                   threads, elapsed, is_sorted(work, n) ? "yes" : "NO",
                   arrays_equal(work, reference, n) ? "yes" : "NO",
                   speedup, efficiency);
        }
        free(original); free(reference); free(work);
    }
    return 0;
}
