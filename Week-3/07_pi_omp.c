#include <stdio.h>
#include <omp.h>

int main() {
    long long n = 1000000;
    double pi = 0.0;
    long long i;

    # pragma omp parallel for reduction(+:pi)
    for (i = 0; i < n; i++) {
        if (i % 2 == 0) pi += 1.0 / (2 * i + 1);
        else pi -= 1.0 / (2 * i + 1);
    }
    
    pi = 4 * pi;

    printf("Value of PI = %lf\n", pi);
    return 0;
}
