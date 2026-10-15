#include <stdio.h>
#include <mpi.h>
int main(int argc,char **argv){
 int rank,size,task,ack;MPI_Status st;MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);MPI_Comm_size(MPI_COMM_WORLD,&size);
 if(rank==0){
   for(int w=1;w<size;w++){task=w;printf("Master: Sending task %d to worker %d\n",task,w);MPI_Send(&task,1,MPI_INT,w,1,MPI_COMM_WORLD);}
   for(int i=1;i<size;i++){MPI_Recv(&ack,1,MPI_INT,MPI_ANY_SOURCE,2,MPI_COMM_WORLD,&st);printf("Master: Received ack from worker %d for task %d\n",st.MPI_SOURCE,ack);}
 }else{
   MPI_Recv(&task,1,MPI_INT,0,1,MPI_COMM_WORLD,&st);printf("Worker %d received task %d\n",rank,task);printf("Worker %d: Acknowledging task %d\n",rank,task);MPI_Send(&task,1,MPI_INT,0,2,MPI_COMM_WORLD);
 }
 MPI_Finalize();return 0;
}
