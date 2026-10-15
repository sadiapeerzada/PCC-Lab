#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000000
int main(void) {
    float *a=malloc((size_t)N*sizeof(*a));
    if(!a){perror("malloc");return 1;}
    unsigned int seed=2468;
    for(int i=0;i<N;i++){seed=seed*1103515245u+12345u;a[i]=(float)(seed%10000u)/100.0f;}
    double total_sum=0.0;
    #pragma omp parallel for reduction(+:total_sum)
    for(int i=0;i<N;i++) total_sum+=a[i];
    printf("Average of array elements: %.6f\n",total_sum/N);
    free(a);return 0;
}
