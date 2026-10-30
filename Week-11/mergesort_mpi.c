/* Week 11 - Problem 11.1 (unsolved part, MPI): Distributed Merge Sort
 * MPI_Scatterv (handles N not divisible by P) -> local sort -> tree merge
 * (log2 P stages using MPI_Send / MPI_Recv) -> result on rank 0.
 * Compile: mpicc -O2 mergesort_mpi.c -o mergesort_mpi
 * Run    : mpirun -np 4 ./mergesort_mpi [N]       (default N = 1000000)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

/* Merge sorted a[na] and b[nb] into a newly allocated array */
static int *merge_arrays(const int *a, int na, const int *b, int nb) {
    int *out = malloc((na + nb) * sizeof(int));
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) out[k++] = (a[i] <= b[j]) ? a[i++] : b[j++];
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
    return out;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int rank, P;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &P);

    int N = (argc > 1) ? atoi(argv[1]) : 1000000;

    int *data = NULL, *ref = NULL;
    double seq_time = 0.0;
    if (rank == 0) {
        data = malloc(N * sizeof(int));
        ref  = malloc(N * sizeof(int));
        srand(12345);
        for (int i = 0; i < N; ++i) data[i] = rand() % 100000;
        memcpy(ref, data, N * sizeof(int));
        double t = MPI_Wtime();
        qsort(ref, N, sizeof(int), cmp_int);          /* sequential baseline */
        seq_time = MPI_Wtime() - t;
    }

    /* ---- Load balancing: chunk sizes differ by at most 1 element ---- */
    int *counts = malloc(P * sizeof(int)), *displs = malloc(P * sizeof(int));
    int base = N / P, rem = N % P, off = 0;
    for (int p = 0; p < P; ++p) {
        counts[p] = base + (p < rem ? 1 : 0);
        displs[p] = off;
        off += counts[p];
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double t_start = MPI_Wtime();

    int local_n = counts[rank];
    int *local = malloc((local_n > 0 ? local_n : 1) * sizeof(int));
    MPI_Scatterv(data, counts, displs, MPI_INT, local, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    /* ---- Local sequential sort ---- */
    qsort(local, local_n, sizeof(int), cmp_int);

    /* ---- Tree-based merge: stage s, partner = rank +/- 2^s ---- */
    int cur_n = local_n;
    for (int step = 1; step < P; step <<= 1) {
        if (rank % (2 * step) == 0) {
            int partner = rank + step;
            if (partner < P) {
                int recv_n;
                MPI_Recv(&recv_n, 1, MPI_INT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                int *recv_buf = malloc((recv_n > 0 ? recv_n : 1) * sizeof(int));
                MPI_Recv(recv_buf, recv_n, MPI_INT, partner, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                int *merged = merge_arrays(local, cur_n, recv_buf, recv_n);
                free(local); free(recv_buf);
                local = merged;
                cur_n += recv_n;
            }
        } else if (rank % (2 * step) == step) {
            int dest = rank - step;
            MPI_Send(&cur_n, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            MPI_Send(local, cur_n, MPI_INT, dest, 1, MPI_COMM_WORLD);
            break;                                  /* this rank is now inactive */
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double par_time = MPI_Wtime() - t_start;

    if (rank == 0) {
        int ok = (cur_n == N);
        for (int i = 0; ok && i < N; ++i) if (local[i] != ref[i]) ok = 0;
        double sp = seq_time / par_time;
        printf("MPI Merge Sort: N=%d, P=%d\n", N, P);
        printf("Sequential qsort time: %lf s\n", seq_time);
        printf("Parallel time        : %lf s\n", par_time);
        printf("Speedup: %lf  Efficiency: %lf\n", sp, sp / P);
        printf("Sorted correctly: %s\n", ok ? "Yes" : "NO (error!)");
        free(data); free(ref);
    }
    free(local); free(counts); free(displs);
    MPI_Finalize();
    return 0;
}
