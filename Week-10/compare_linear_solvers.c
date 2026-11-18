// Unsolved Problem 2: Compare Methods for Solving Linear Equations
// Aligarh Muslim University, Lab V, Week 10

#include <stdio.h>
#include <math.h>
#include <omp.h>
#define N 32
#define MAX_ITER 30000
#define TOL 1e-6
static double residual(const double *x) {
    double worst = 0;
    for (int i = 0; i < N; i++) {
        double left = i ? x[i-1] : 0;
        double right = i+1 < N ? x[i+1] : 0;
        double r = fabs(2*x[i]-left-right-1);
        if (r > worst) worst = r;
    }
    return worst;
}
int main(void) {
    double old[N] = {0}, next[N] = {0}, gs[N] = {0};
    int jacobi_iters = 0, gs_iters = 0;
    double t = omp_get_wtime();
    for (int it = 0; it < MAX_ITER; it++) {
        double change = 0;
        #pragma omp parallel for reduction(max:change)
        for (int i = 0; i < N; i++) {
            double left = i ? old[i-1] : 0;
            double right = i+1 < N ? old[i+1] : 0;
            next[i] = (1+left+right)/2.0;
            double d = fabs(next[i]-old[i]);
            if (d > change) change = d;
        }
        for (int i = 0; i < N; i++) old[i] = next[i];
        jacobi_iters = it+1;
        if (change < TOL) break;
    }
    double tj = omp_get_wtime()-t;
    t = omp_get_wtime();
    for (int it = 0; it < MAX_ITER; it++) {
        double change = 0;
        for (int i = 0; i < N; i++) {
            double left = i ? gs[i-1] : 0;
            double right = i+1 < N ? gs[i+1] : 0;
            double value = (1+left+right)/2.0;
            double d = fabs(value-gs[i]);
            if (d > change) change = d;
            gs[i] = value;
        }
        gs_iters = it+1;
        if (change < TOL) break;
    }
    double tg = omp_get_wtime()-t;
    printf("Jacobi: iterations=%d residual=%.8g time=%.6f s\n",
           jacobi_iters, residual(old), tj);
    printf("Gauss-Seidel: iterations=%d residual=%.8g time=%.6f s\n",
           gs_iters, residual(gs), tg);
    return 0;
}
