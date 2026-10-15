#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc,char **argv){
 int rank,size,N=4;int *A=NULL,*x=NULL,*localA,*y=NULL,*localy;
 MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);MPI_Comm_size(MPI_COMM_WORLD,&size);
 if(argc>1)N=atoi(argv[1]);
 if(N<=0||N%size!=0){if(rank==0)fprintf(stderr,"N must be positive and divisible by process count.\n");MPI_Finalize();return 1;}
 int rows=N/size;
 localA=malloc((size_t)rows*N*sizeof(int));localy=malloc((size_t)rows*sizeof(int));x=malloc((size_t)N*sizeof(int));
 if(rank==0){A=malloc((size_t)N*N*sizeof(int));y=malloc((size_t)N*sizeof(int));if(!A||!x||!y)MPI_Abort(MPI_COMM_WORLD,1);
   for(int i=0;i<N;i++){x[i]=1;for(int j=0;j<N;j++)A[i*N+j]=(i*N+j+1)%10;}
 }
 if(!localA||!localy||!x)MPI_Abort(MPI_COMM_WORLD,1);
 MPI_Bcast(x,N,MPI_INT,0,MPI_COMM_WORLD);
 MPI_Scatter(A,rows*N,MPI_INT,localA,rows*N,MPI_INT,0,MPI_COMM_WORLD);
 for(int i=0;i<rows;i++){localy[i]=0;for(int j=0;j<N;j++)localy[i]+=localA[i*N+j]*x[j];}
 MPI_Gather(localy,rows,MPI_INT,y,rows,MPI_INT,0,MPI_COMM_WORLD);
 if(rank==0){printf("Result vector y (first up to 10 elements):");for(int i=0;i<N&&i<10;i++)printf(" %d",y[i]);puts("");free(A);free(x);free(y);}
 free(localA);free(localy);if(rank!=0)free(x);MPI_Finalize();return 0;
}
