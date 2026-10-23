#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 4
#define MAX_ITER 10000
#define TOL 1e-9

int main(void) {
    const double A[N][N] = {
        {10, -1,  2,  0},
        {-1, 11, -1,  3},
        { 2, -1, 10, -1},
        { 0,  3, -1,  8}
    };
    const double b[N] = {6, 25, -11, 15};
    double x[N] = {0, 0, 0, 0};
    int iter;
    double change = 0.0;

    double start = omp_get_wtime();
    for (iter = 1; iter <= MAX_ITER; ++iter) {
        change = 0.0;
        for (int i = 0; i < N; ++i) {
            double sum = b[i];
            for (int j = 0; j < N; ++j)
                if (j != i) sum -= A[i][j] * x[j];
            double next = sum / A[i][i];
            double delta = fabs(next - x[i]);
            if (delta > change) change = delta;
            x[i] = next;
        }
        if (change < TOL) break;
    }
    double elapsed = omp_get_wtime() - start;

    printf("Sequential Gauss-Seidel\nIterations: %d\nMax change: %.3e\nTime: %.8f s\n",
           iter <= MAX_ITER ? iter : MAX_ITER, change, elapsed);
    for (int i = 0; i < N; ++i) printf("x[%d] = %.10f\n", i, x[i]);
    return 0;
}
