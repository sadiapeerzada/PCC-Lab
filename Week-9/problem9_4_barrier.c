#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
int main(int argc,char **argv){
 int rank;MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 printf("Process %d: Before barrier\n",rank);fflush(stdout);
 usleep((useconds_t)rank*100000);
 MPI_Barrier(MPI_COMM_WORLD);
 printf("Process %d: After barrier\n",rank);fflush(stdout);
 MPI_Finalize();return 0;
}
