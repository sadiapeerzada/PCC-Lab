#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define TOTAL_N 12
int main(int argc,char **argv){
 int rank,size,sendbuf[TOTAL_N],local_n,*recvbuf;MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);MPI_Comm_size(MPI_COMM_WORLD,&size);
 if(TOTAL_N%size!=0){if(rank==0)fprintf(stderr,"Process count must divide %d.\n",TOTAL_N);MPI_Finalize();return 1;}
 local_n=TOTAL_N/size;recvbuf=malloc((size_t)local_n*sizeof(int));if(!recvbuf)MPI_Abort(MPI_COMM_WORLD,1);
 if(rank==0)for(int i=0;i<TOTAL_N;i++)sendbuf[i]=i;
 MPI_Scatter(sendbuf,local_n,MPI_INT,recvbuf,local_n,MPI_INT,0,MPI_COMM_WORLD);
 printf("Process %d received:",rank);for(int i=0;i<local_n;i++)printf(" %d",recvbuf[i]);puts("");
 free(recvbuf);MPI_Finalize();return 0;
}
