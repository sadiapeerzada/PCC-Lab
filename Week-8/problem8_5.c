#include <stdio.h>
#include <mpi.h>
int main(int argc,char **argv){
 int rank,size,color,newrank;MPI_Comm sub;MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);MPI_Comm_size(MPI_COMM_WORLD,&size);
 color=rank%2;MPI_Comm_split(MPI_COMM_WORLD,color,rank,&sub);
 if(sub!=MPI_COMM_NULL){MPI_Comm_rank(sub,&newrank);printf("Global Rank %d: New Rank %d in %s Comm\n",rank,newrank,color==0?"Even":"Odd");MPI_Comm_free(&sub);}
 MPI_Finalize();return 0;
}
