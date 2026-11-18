// Unsolved Problem 11.1(b): Parallel Merge Sort (MPI, Load Balancing)
// Aligarh Muslim University, Lab V, Week 11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#define N 10003
static int cmp(const void *a,const void *b) {
    int x=*(const int *)a,y=*(const int *)b;
    return (x>y)-(x<y);
}
static int *merge_sorted(const int *a,int na,const int *b,int nb) {
    int *out=malloc((size_t)(na+nb)*sizeof(int));
    if(!out) MPI_Abort(MPI_COMM_WORLD,1);
    int i=0,j=0,k=0;
    while(i<na && j<nb) out[k++]=a[i]<=b[j]?a[i++]:b[j++];
    while(i<na) out[k++]=a[i++];
    while(j<nb) out[k++]=b[j++];
    return out;
}
int main(int argc,char **argv) {
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int *counts=malloc((size_t)size*sizeof(int));
    int *displs=malloc((size_t)size*sizeof(int));
    if(!counts || !displs) MPI_Abort(MPI_COMM_WORLD,1);
    int offset=0;
    for(int r=0;r<size;r++) {
        counts[r]=N/size+(r<N%size);
        displs[r]=offset;
        offset+=counts[r];
    }
    int *original=NULL, *reference=NULL;
    double serial_time=0;
    if(rank==0) {
        original=malloc((size_t)N*sizeof(int));
        reference=malloc((size_t)N*sizeof(int));
        if(!original || !reference) MPI_Abort(MPI_COMM_WORLD,1);
        srand(2026);
        for(int i=0;i<N;i++) original[i]=rand();
        memcpy(reference,original,(size_t)N*sizeof(int));
        double ts=MPI_Wtime();
        qsort(reference,N,sizeof(int),cmp);
        serial_time=MPI_Wtime()-ts;
    }
    int local_n=counts[rank];
    int *local=malloc((size_t)(local_n?local_n:1)*sizeof(int));
    if(!local) MPI_Abort(MPI_COMM_WORLD,1);
    MPI_Barrier(MPI_COMM_WORLD);
    double start=MPI_Wtime();
    MPI_Scatterv(original,counts,displs,MPI_INT,local,local_n,MPI_INT,
                 0,MPI_COMM_WORLD);
    qsort(local,local_n,sizeof(int),cmp);
    for(int step=1;step<size;step*=2) {
        if(rank%(2*step)==step) {
            int dest=rank-step;
            MPI_Send(&local_n,1,MPI_INT,dest,0,MPI_COMM_WORLD);
            MPI_Send(local,local_n,MPI_INT,dest,1,MPI_COMM_WORLD);
            break;
        }
        if(rank%(2*step)==0 && rank+step<size) {
            int from=rank+step,other_n;
            MPI_Recv(&other_n,1,MPI_INT,from,0,MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            int *other=malloc((size_t)(other_n?other_n:1)*sizeof(int));
            if(!other) MPI_Abort(MPI_COMM_WORLD,1);
            MPI_Recv(other,other_n,MPI_INT,from,1,MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            int *joined=merge_sorted(local,local_n,other,other_n);
            free(local); free(other);
            local=joined;
            local_n+=other_n;
        }
    }
    double elapsed=MPI_Wtime()-start, max_elapsed=0;
    MPI_Reduce(&elapsed,&max_elapsed,1,MPI_DOUBLE,MPI_MAX,0,
               MPI_COMM_WORLD);
    if(rank==0) {
        int valid=local_n==N && memcmp(local,reference,(size_t)N*sizeof(int))==0;
        printf("N=%d Processes=%d Sorted=%s\n",N,size,valid?"YES":"NO");
        printf("Sequential qsort: %.6f s\nMPI sort+communication: %.6f s\n",
               serial_time,max_elapsed);
        double speedup=max_elapsed>0?serial_time/max_elapsed:0;
        printf("Speedup=%.3f Efficiency=%.3f\n",speedup,speedup/size);
    }
    free(local); free(counts); free(displs);
    if(rank==0) { free(original);free(reference); }
    MPI_Finalize();return 0;
}
