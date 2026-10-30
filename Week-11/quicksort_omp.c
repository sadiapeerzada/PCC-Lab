/* Week 11 - Problem 11.1 (solved): Parallel Quick Sort using OpenMP tasks
 * Compile: gcc -O2 -fopenmp quicksort_omp.c -o quicksort_omp
 * Run    : ./quicksort_omp [threshold]   (default threshold = 1024)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

static int THRESHOLD_SIZE = 1024;   /* below this size, sort sequentially */

static void swap_int(int *a, int *b) { int t = *a; *a = *b; *b = t; }

/* Overflow-safe comparator for qsort */
static int compare_qsort_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

/* Lomuto partition (sequential) with median-of-three pivot to avoid
 * worst-case behaviour on already-sorted data. */
static int partition_arr(int *arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low])  swap_int(&arr[mid], &arr[low]);
    if (arr[high] < arr[low]) swap_int(&arr[high], &arr[low]);
    if (arr[mid] < arr[high]) swap_int(&arr[mid], &arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot) { i++; swap_int(&arr[i], &arr[j]); }
    swap_int(&arr[i + 1], &arr[high]);
    return i + 1;
}

static void parallel_quick_sort_recursive(int *arr, int low, int high) {
    if (low >= high) return;
    if (high - low + 1 <= THRESHOLD_SIZE) {      /* task cutoff */
        qsort(arr + low, high - low + 1, sizeof(int), compare_qsort_int);
        return;
    }
    int pi = partition_arr(arr, low, high);

    #pragma omp task
    parallel_quick_sort_recursive(arr, low, pi - 1);
    #pragma omp task
    parallel_quick_sort_recursive(arr, pi + 1, high);
    /* No taskwait needed: the implicit barrier at the end of the parallel
     * region guarantees every generated task finishes. */
}

static void initiate_parallel_quick_sort(int *arr, int N, int num_threads) {
    omp_set_num_threads(num_threads);
    #pragma omp parallel
    {
        #pragma omp single nowait     /* one thread creates the root task */
        parallel_quick_sort_recursive(arr, 0, N - 1);
    }
}

static int is_sorted_arr(const int *arr, int N) {
    for (int i = 0; i < N - 1; ++i) if (arr[i] > arr[i + 1]) return 0;
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) THRESHOLD_SIZE = atoi(argv[1]);
    int N_vals[] = {100000, 500000, 1000000, 5000000};
    int thr_vals[] = {1, 2, 4, 8};
    int nN = sizeof(N_vals) / sizeof(N_vals[0]);
    int nT = sizeof(thr_vals) / sizeof(thr_vals[0]);

    printf("Parallel Quick Sort Analysis (THRESHOLD_SIZE = %d)\n", THRESHOLD_SIZE);
    printf("--------------------------------------------------\n");

    for (int a = 0; a < nN; ++a) {
        int N = N_vals[a];
        printf("\n--- Sorting N = %d elements ---\n", N);
        int *orig = malloc(N * sizeof(int));
        int *work = malloc(N * sizeof(int));
        if (!orig || !work) { fprintf(stderr, "malloc failed\n"); return 1; }
        srand(12345);
        for (int i = 0; i < N; ++i) orig[i] = rand() % 100000;

        memcpy(work, orig, N * sizeof(int));
        double t0 = omp_get_wtime();
        qsort(work, N, sizeof(int), compare_qsort_int);
        double seq = omp_get_wtime() - t0;
        printf("Sequential qsort time: %lf s  (sorted: %s)\n", seq,
               is_sorted_arr(work, N) ? "Yes" : "NO");

        for (int b = 0; b < nT; ++b) {
            int T = thr_vals[b];
            memcpy(work, orig, N * sizeof(int));
            t0 = omp_get_wtime();
            initiate_parallel_quick_sort(work, N, T);
            double par = omp_get_wtime() - t0;
            double sp = par > 0 ? seq / par : 0.0;
            printf("Threads=%d  Time: %lf s  Speedup: %lf  Efficiency: %lf  Sorted: %s\n",
                   T, par, sp, sp / T, is_sorted_arr(work, N) ? "Yes" : "NO");
        }
        free(orig); free(work);
    }

    /* Threshold experiment (Requirement 5) */
    printf("\n=== Threshold experiment: N=5000000, 4 threads ===\n");
    int N = 5000000;
    int *orig = malloc(N * sizeof(int)), *work = malloc(N * sizeof(int));
    srand(12345);
    for (int i = 0; i < N; ++i) orig[i] = rand() % 100000;
    int thresholds[] = {16, 64, 256, 1024, 4096, 16384, 65536};
    for (int k = 0; k < 7; ++k) {
        THRESHOLD_SIZE = thresholds[k];
        memcpy(work, orig, N * sizeof(int));
        double t0 = omp_get_wtime();
        initiate_parallel_quick_sort(work, N, 4);
        printf("Threshold=%6d  Time: %lf s  Sorted: %s\n", THRESHOLD_SIZE,
               omp_get_wtime() - t0, is_sorted_arr(work, N) ? "Yes" : "NO");
    }
    free(orig); free(work);
    return 0;
}
