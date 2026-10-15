#include <stdio.h>
#include <stdlib.h>
#define N 1000
int main(void) {
    int *a=malloc((size_t)N*N*sizeof(*a)), *b=malloc((size_t)N*N*sizeof(*b));
    if(!a||!b){perror("malloc");free(a);free(b);return 1;}
    for(int i=0;i<N;i++)for(int j=0;j<N;j++)a[i*N+j]=i*N+j;
    #pragma omp parallel for
    for(int i=0;i<N;i++)for(int j=0;j<N;j++)b[j*N+i]=a[i*N+j];
    puts("Top-left 4x4 of A and its transpose B:");
    for(int i=0;i<4;i++){for(int j=0;j<4;j++)printf("%5d ",a[i*N+j]);printf(" | ");for(int j=0;j<4;j++)printf("%5d ",b[i*N+j]);puts("");}
    free(a);free(b);return 0;
}
