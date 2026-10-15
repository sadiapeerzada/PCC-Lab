#include <stdio.h>
#include <mpi.h>
int main(int argc,char **argv){
 int rank,size,send_to,recv_from,send_value; MPI_Status st;
 MPI_Init(&argc,&argv); MPI_Comm_rank(MPI_COMM_WORLD,&rank); MPI_Comm_size(MPI_COMM_WORLD,&size);
 if(size<2){if(rank==0)fprintf(stderr,"Run with at least 2 processes.\n");MPI_Finalize();return 1;}
 send_to=(rank+1)%size; recv_from=(rank-1+size)%size; send_value=rank;
 /* Even ranks send first, odd ranks receive first to avoid a blocking-send cycle. */
 if(rank%2==0){
   MPI_Send(&send_value,1,MPI_INT,send_to,10,MPI_COMM_WORLD);
   MPI_Recv(&send_value,1,MPI_INT,recv_from,10,MPI_COMM_WORLD,&st);
 }else{
   MPI_Recv(&send_value,1,MPI_INT,recv_from,10,MPI_COMM_WORLD,&st);
   MPI_Send(&rank,1,MPI_INT,send_to,10,MPI_COMM_WORLD);
 }
 printf("Process %d received message from process %d\n",rank,send_value);
 MPI_Finalize();return 0;
}
