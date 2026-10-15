#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
static int isPrime(int n){if(n<2)return 0;if(n==2)return 1;if(n%2==0)return 0;for(int d=3;d<=n/d;d+=2)if(n%d==0)return 0;return 1;}
int main(int argc,char **argv){
 int rank,size,N=20;MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);MPI_Comm_size(MPI_COMM_WORLD,&size);
 if(argc>1)N=atoi(argv[1]);if(N<0){if(rank==0)fprintf(stderr,"N must be non-negative.\n");MPI_Finalize();return 1;}
 int start=(int)((long long)rank*N/size),end=(int)((long long)(rank+1)*N/size)-1;
 printf("Process %d checking range [%d, %d]\n",rank,start,end);
 for(int n=start;n<=end;n++)if(isPrime(n))printf("Process %d: %d is prime\n",rank,n);
 MPI_Finalize();return 0;
}
