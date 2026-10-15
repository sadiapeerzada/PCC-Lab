#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000000
int main(void) {
    double *a=malloc((size_t)N*sizeof(*a)), *b=malloc((size_t)N*sizeof(*b));
    if(!a||!b){perror("malloc");free(a);free(b);return 1;}
    for(int i=0;i<N;i++){a[i]=(double)i*0.5;b[i]=(double)i*0.25;}
    double serial=0, parallel=0, t=omp_get_wtime();
    for(int i=0;i<N;i++) serial+=a[i]*b[i];
    double ts=omp_get_wtime()-t; t=omp_get_wtime();
    #pragma omp parallel for reduction(+:parallel)
    for(int i=0;i<N;i++) parallel+=a[i]*b[i];
    double tp=omp_get_wtime()-t;
    printf("Serial Dot Product: %.6f (%.6f s)\n",serial,ts);
    printf("Parallel Dot Product (reduction): %.6f (%.6f s)\n",parallel,tp);
    printf("Absolute difference: %.9f\n",serial-parallel);
    free(a);free(b);return 0;
}
