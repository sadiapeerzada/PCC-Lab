#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000000
int main(void) {
    long long *a = malloc((size_t)N * sizeof(*a));
    if (!a) { perror("malloc"); return 1; }
    for (int i=0;i<N;i++) a[i]=(long long)i+1;
    long long serial=0, critical_sum=0, atomic_sum=0, reduction_sum=0;
    double t=omp_get_wtime();
    for(int i=0;i<N;i++) serial+=a[i];
    double serial_time=omp_get_wtime()-t;
    t=omp_get_wtime();
    #pragma omp parallel for
    for(int i=0;i<N;i++) {
        #pragma omp critical
        critical_sum+=a[i];
    }
    double critical_time=omp_get_wtime()-t;
    t=omp_get_wtime();
    #pragma omp parallel for
    for(int i=0;i<N;i++) {
        #pragma omp atomic
        atomic_sum+=a[i];
    }
    double atomic_time=omp_get_wtime()-t;
    t=omp_get_wtime();
    #pragma omp parallel for reduction(+:reduction_sum)
    for(int i=0;i<N;i++) reduction_sum+=a[i];
    double reduction_time=omp_get_wtime()-t;
    printf("Serial Sum: %lld (%.6f s)\n",serial,serial_time);
    printf("Critical Sum: %lld (%.6f s)\n",critical_sum,critical_time);
    printf("Atomic Sum: %lld (%.6f s)\n",atomic_sum,atomic_time);
    printf("Reduction Sum: %lld (%.6f s)\n",reduction_sum,reduction_time);
    free(a);
    return !(serial==critical_sum && serial==atomic_sum && serial==reduction_sum);
}
