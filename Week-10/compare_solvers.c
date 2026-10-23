#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 4
#define MAX_ITER 10000
#define TOL 1e-9

static const double A[N][N] = {
    {10, -1,  2,  0},
    {-1, 11, -1,  3},
    { 2, -1, 10, -1},
    { 0,  3, -1,  8}
};
static const double b[N] = {6, 25, -11, 15};

static double residual_inf(const double x[N]) {
    double maxr = 0.0;
    for (int i = 0; i < N; ++i) {
        double r = -b[i];
        for (int j = 0; j < N; ++j) r += A[i][j] * x[j];
        if (fabs(r) > maxr) maxr = fabs(r);
    }
    return maxr;
}

static void jacobi(double x[N], int *iterations, double *elapsed) {
    double old[N] = {0}, next[N] = {0};
    double start = omp_get_wtime();
    for (int it = 1; it <= MAX_ITER; ++it) {
        double change = 0.0;
        for (int i = 0; i < N; ++i) {
            double sum = b[i];
            for (int j = 0; j < N; ++j)
                if (j != i) sum -= A[i][j] * old[j];
            next[i] = sum / A[i][i];
            if (fabs(next[i] - old[i]) > change) change = fabs(next[i] - old[i]);
        }
        for (int i = 0; i < N; ++i) old[i] = next[i];
        if (change < TOL) { *iterations = it; break; }
        *iterations = it;
    }
    for (int i = 0; i < N; ++i) x[i] = old[i];
    *elapsed = omp_get_wtime() - start;
}

static void gauss_seidel(double x[N], int *iterations, double *elapsed) {
    for (int i = 0; i < N; ++i) x[i] = 0.0;
    double start = omp_get_wtime();
    for (int it = 1; it <= MAX_ITER; ++it) {
        double change = 0.0;
        for (int i = 0; i < N; ++i) {
            double sum = b[i];
            for (int j = 0; j < N; ++j)
                if (j != i) sum -= A[i][j] * x[j];
            double next = sum / A[i][i];
            if (fabs(next - x[i]) > change) change = fabs(next - x[i]);
            x[i] = next;
        }
        *iterations = it;
        if (change < TOL) break;
    }
    *elapsed = omp_get_wtime() - start;
}

int main(void) {
    double xj[N], xg[N], tj, tg;
    int ij = 0, ig = 0;
    jacobi(xj, &ij, &tj);
    gauss_seidel(xg, &ig, &tg);

    puts("Jacobi vs Gauss-Seidel (same diagonally dominant system)");
    printf("Jacobi:        iterations=%d time=%.8f s residual_inf=%.3e\n",
           ij, tj, residual_inf(xj));
    printf("Gauss-Seidel:  iterations=%d time=%.8f s residual_inf=%.3e\n",
           ig, tg, residual_inf(xg));
    puts("Solution (Gauss-Seidel):");
    for (int i = 0; i < N; ++i) printf("x[%d] = %.10f\n", i, xg[i]);
    return 0;
}
