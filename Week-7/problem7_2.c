#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>
#define N 1000000
int main(void) {
    int *a=malloc((size_t)N*sizeof(*a));
    if(!a){perror("malloc");return 1;}
    unsigned int seed=12345;
    for(int i=0;i<N;i++){ seed=seed*1103515245u+12345u; a[i]=(int)((seed>>8)%1000000u); }
    int max_val=INT_MIN, min_val=INT_MAX;
    #pragma omp parallel for reduction(max:max_val) reduction(min:min_val)
    for(int i=0;i<N;i++){ if(a[i]>max_val) max_val=a[i]; if(a[i]<min_val) min_val=a[i]; }
    printf("Max Value: %d\nMin Value: %d\n",max_val,min_val);
    free(a); return 0;
}
