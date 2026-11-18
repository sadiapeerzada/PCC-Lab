// Unsolved Problem 11.1(a): Parallel Merge Sort (OpenMP)
// Aligarh Muslim University, Lab V, Week 11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#define N 100000
#define CUTOFF 2048
static int cmp(const void *a, const void *b) {
    int x=*(const int *)a, y=*(const int *)b;
    return (x>y)-(x<y);
}
static void merge(int *a, int *tmp, int lo, int mid, int hi) {
    int i=lo, j=mid, k=lo;
    while (i<mid && j<hi)
        tmp[k++] = a[i]<=a[j] ? a[i++] : a[j++];
    while (i<mid) tmp[k++] = a[i++];
    while (j<hi) tmp[k++] = a[j++];
    for (i=lo; i<hi; i++) a[i]=tmp[i];
}
static void mergesort(int *a, int *tmp, int lo, int hi) {
    if (hi-lo<=1) return;
    if (hi-lo<=CUTOFF) {
        qsort(a+lo, (size_t)(hi-lo), sizeof(int), cmp);
        return;
    }
    int mid=lo+(hi-lo)/2;
    #pragma omp task shared(a,tmp) firstprivate(lo,mid)
    mergesort(a,tmp,lo,mid);
    #pragma omp task shared(a,tmp) firstprivate(mid,hi)
    mergesort(a,tmp,mid,hi);
    #pragma omp taskwait
    merge(a,tmp,lo,mid,hi);
}
static void parallel_sort(int *a,int *tmp,int n,int threads) {
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp single
        mergesort(a,tmp,0,n);
    }
}
int main(void) {
    int *original=malloc((size_t)N*sizeof(int));
    int *reference=malloc((size_t)N*sizeof(int));
    int *a=malloc((size_t)N*sizeof(int));
    int *tmp=malloc((size_t)N*sizeof(int));
    if (!original || !reference || !a || !tmp) return 1;
    srand(11);
    for(int i=0;i<N;i++) original[i]=rand();
    memcpy(reference,original,(size_t)N*sizeof(int));
    double t=omp_get_wtime();
    qsort(reference,N,sizeof(int),cmp);
    double serial=omp_get_wtime()-t;
    printf("Sequential qsort: %.6f s\n",serial);
    int counts[]={1,2,4};
    for(int k=0;k<3;k++) {
        memcpy(a,original,(size_t)N*sizeof(int));
        t=omp_get_wtime();
        parallel_sort(a,tmp,N,counts[k]);
        double sec=omp_get_wtime()-t;
        double speedup=sec>0?serial/sec:0;
        printf("Threads=%d time=%.6f speedup=%.3f efficiency=%.3f %s\n",
               counts[k],sec,speedup,speedup/counts[k],
               memcmp(a,reference,(size_t)N*sizeof(int))==0?"SORTED":"ERROR");
    }
    free(original); free(reference); free(a); free(tmp);
    return 0;
}
