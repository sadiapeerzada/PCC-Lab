// Unsolved Problem 1: Parallel Gauss–Seidel Method (OpenMP)
// Aligarh Muslim University, Lab V, Week 10

#include <stdio.h>
#include <math.h>
#include <omp.h>
#define N 32
#define MAX_ITER 30000
#define TOL 1e-6
int main(void) {
    double x[N] = {0};
    int iterations = 0;
    double max_change = 0, t = omp_get_wtime();
    for (int iter = 0; iter < MAX_ITER; iter++) {
        max_change = 0;
        #pragma omp parallel for reduction(max:max_change)
        for (int i = 0; i < N; i += 2) {
            double left = i ? x[i-1] : 0;
            double right = i+1 < N ? x[i+1] : 0;
            double next = (1.0+left+right)/2.0;
            double diff = fabs(next-x[i]);
            x[i] = next;
            if (diff > max_change) max_change = diff;
        }
        #pragma omp parallel for reduction(max:max_change)
        for (int i = 1; i < N; i += 2) {
            double left = x[i-1];
            double right = i+1 < N ? x[i+1] : 0;
            double next = (1.0+left+right)/2.0;
            double diff = fabs(next-x[i]);
            x[i] = next;
            if (diff > max_change) max_change = diff;
        }
        iterations = iter + 1;
        if (max_change < TOL) break;
    }
    double max_residual = 0;
    for (int i = 0; i < N; i++) {
        double left = i ? x[i-1] : 0;
        double right = i+1 < N ? x[i+1] : 0;
        double r = fabs(2*x[i] - left - right - 1);
        if (r > max_residual) max_residual = r;
    }
    printf("Iterations: %d\nMax change: %.9g\n", iterations, max_change);
    printf("Max residual: %.9g\nTime: %.6f s\n", max_residual,
           omp_get_wtime()-t);
    printf("First four x: %.4f %.4f %.4f %.4f\n",
           x[0], x[1], x[2], x[3]);
    return 0;
}
