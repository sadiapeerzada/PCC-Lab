#include <stdio.h>
#include <mpi.h>
int main(int argc,char **argv){
 int rank,size,value=0; MPI_Status st; const int rounds=5;
 MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);MPI_Comm_size(MPI_COMM_WORLD,&size);
 if(size!=2){if(rank==0)fprintf(stderr,"Run exactly 2 processes.\n");MPI_Finalize();return 1;}
 if(rank==0){
   for(int r=1;r<=rounds;r++){printf("Process 0: Sending %d to Process 1 (round %d)\n",value,r);MPI_Send(&value,1,MPI_INT,1,0,MPI_COMM_WORLD);MPI_Recv(&value,1,MPI_INT,1,1,MPI_COMM_WORLD,&st);printf("Process 0: Received %d from Process 1\n",value);}
 }else{
   for(int r=1;r<=rounds;r++){MPI_Recv(&value,1,MPI_INT,0,0,MPI_COMM_WORLD,&st);printf("Process 1: Received %d from Process 0, sending %d back (round %d)\n",value,value+1,r);value++;MPI_Send(&value,1,MPI_INT,0,1,MPI_COMM_WORLD);}
 }
 MPI_Finalize();return 0;
}
