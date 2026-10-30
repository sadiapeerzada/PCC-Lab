/* Week 11 - Problem 11.1 (unsolved part, OpenMP): Parallel Merge Sort
 * Compile: gcc -O2 -fopenmp mergesort_omp.c -o mergesort_omp
 * Run    : ./mergesort_omp [threshold]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

static int THRESHOLD_SIZE = 4096;

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

/* Sequential merge of arr[l..m] and arr[m+1..r] using tmp */
static void merge(int *arr, int *tmp, int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) tmp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while (i <= m) tmp[k++] = arr[i++];
    while (j <= r) tmp[k++] = arr[j++];
    memcpy(arr + l, tmp + l, (r - l + 1) * sizeof(int));
}

static void merge_sort_seq(int *arr, int *tmp, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    merge_sort_seq(arr, tmp, l, m);
    merge_sort_seq(arr, tmp, m + 1, r);
    merge(arr, tmp, l, m, r);
}

static void merge_sort_par(int *arr, int *tmp, int l, int r) {
    if (l >= r) return;
    if (r - l + 1 <= THRESHOLD_SIZE) { merge_sort_seq(arr, tmp, l, r); return; }
    int m = l + (r - l) / 2;
    #pragma omp task
    merge_sort_par(arr, tmp, l, m);
    #pragma omp task
    merge_sort_par(arr, tmp, m + 1, r);
    #pragma omp taskwait          /* both halves must be sorted before merging */
    merge(arr, tmp, l, m, r);
}

static void run_parallel(int *arr, int *tmp, int N, int T) {
    omp_set_num_threads(T);
    #pragma omp parallel
    {
        #pragma omp single
        merge_sort_par(arr, tmp, 0, N - 1);
    }
}

static int is_sorted_arr(const int *a, int N) {
    for (int i = 0; i < N - 1; ++i) if (a[i] > a[i + 1]) return 0;
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) THRESHOLD_SIZE = atoi(argv[1]);
    int N_vals[] = {100000, 500000, 1000000, 5000000};
    int T_vals[] = {1, 2, 4, 8};
    printf("Parallel Merge Sort (OpenMP tasks), THRESHOLD_SIZE = %d\n", THRESHOLD_SIZE);
    printf("------------------------------------------------------\n");

    for (int a = 0; a < 4; ++a) {
        int N = N_vals[a];
        printf("\n--- N = %d ---\n", N);
        int *orig = malloc(N * sizeof(int)), *work = malloc(N * sizeof(int));
        int *tmp = malloc(N * sizeof(int));
        if (!orig || !work || !tmp) { fprintf(stderr, "malloc failed\n"); return 1; }
        srand(12345);
        for (int i = 0; i < N; ++i) orig[i] = rand() % 100000;

        memcpy(work, orig, N * sizeof(int));
        double t0 = omp_get_wtime();
        merge_sort_seq(work, tmp, 0, N - 1);
        double seq = omp_get_wtime() - t0;
        printf("Sequential merge sort: %lf s (sorted: %s)\n", seq,
               is_sorted_arr(work, N) ? "Yes" : "NO");

        for (int b = 0; b < 4; ++b) {
            int T = T_vals[b];
            memcpy(work, orig, N * sizeof(int));
            t0 = omp_get_wtime();
            run_parallel(work, tmp, N, T);
            double par = omp_get_wtime() - t0;
            double sp = seq / par;
            printf("Threads=%d  Time: %lf s  Speedup: %lf  Efficiency: %lf  Sorted: %s\n",
                   T, par, sp, sp / T, is_sorted_arr(work, N) ? "Yes" : "NO");
        }
        free(orig); free(work); free(tmp);
    }
    return 0;
}
