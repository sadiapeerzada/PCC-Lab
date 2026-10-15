#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
int main(int argc,char **argv){
 int rank,local,gmax,gmin;MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 srand((unsigned)time(NULL)+(unsigned)rank);local=rand()%1000;
 MPI_Allreduce(&local,&gmax,1,MPI_INT,MPI_MAX,MPI_COMM_WORLD);
 MPI_Allreduce(&local,&gmin,1,MPI_INT,MPI_MIN,MPI_COMM_WORLD);
 printf("Process %d generated %d. Global Max: %d, Global Min: %d\n",rank,local,gmax,gmin);
 MPI_Finalize();return 0;
}
