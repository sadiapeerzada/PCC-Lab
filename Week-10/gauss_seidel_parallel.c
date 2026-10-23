#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/*
 * Parallel red-black Gauss-Seidel demonstration for a 1-D Poisson system:
 * - two color phases are separated by an OpenMP barrier
 * - points of the same parity do not depend on each other
 * - this is a safe parallel ordering, unlike naively parallelizing dense GS
 */
#define N 100000
#define MAX_ITER 20000
#define TOL 1e-7

int main(void) {
    double *x = calloc(N, sizeof *x);
    double *next = calloc(N, sizeof *next);
    if (!x || !next) {
        fprintf(stderr, "Memory allocation failed\n");
        free(x); free(next);
        return 1;
    }

    /* Solve -x[i-1] + 2*x[i] - x[i+1] = 1, with zero boundary values. */
    int iter = 0;
    double max_change = 0.0;
    double start = omp_get_wtime();

    for (iter = 1; iter <= MAX_ITER; ++iter) {
        max_change = 0.0;
        #pragma omp parallel reduction(max:max_change) shared(x, next)
        {
            for (int color = 0; color < 2; ++color) {
                #pragma omp for schedule(static) reduction(max:max_change)
                for (int i = 1 + color; i < N - 1; i += 2) {
                    double updated = (1.0 + x[i - 1] + x[i + 1]) / 2.0;
                    double delta = fabs(updated - x[i]);
                    if (delta > max_change) max_change = delta;
                    next[i] = updated;
                }
                #pragma omp barrier
                #pragma omp single
                {
                    for (int i = 1 + color; i < N - 1; i += 2)
                        x[i] = next[i];
                }
                /* implicit barrier at end of single ensures writes are visible */
            }
        }
        if (max_change < TOL) break;
    }

    double elapsed = omp_get_wtime() - start;
    printf("Parallel red-black Gauss-Seidel (1-D Poisson)\n");
    printf("N=%d, threads=%d, iterations=%d, max change=%.3e, time=%.6f s\n",
           N, omp_get_max_threads(), iter <= MAX_ITER ? iter : MAX_ITER,
           max_change, elapsed);
    printf("Sample values: x[1]=%.6f, x[N/2]=%.6f, x[N-2]=%.6f\n",
           x[1], x[N / 2], x[N - 2]);
    free(x); free(next);
    return 0;
}
