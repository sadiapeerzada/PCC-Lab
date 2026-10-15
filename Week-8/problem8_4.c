#include <stdio.h>
#include <string.h>
#include <mpi.h>
int main(int argc,char **argv){
 int rank,size;char msg[]="Hello non-blocking!",received[100]={0};MPI_Request req;MPI_Status st;
 MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);MPI_Comm_size(MPI_COMM_WORLD,&size);
 if(size!=2){if(rank==0)fprintf(stderr,"Run exactly 2 processes.\n");MPI_Finalize();return 1;}
 if(rank==0){printf("Process 0: Starting non-blocking send.\n");MPI_Isend(msg,(int)strlen(msg)+1,MPI_CHAR,1,7,MPI_COMM_WORLD,&req);printf("Process 0: Doing other work while message is in transit...\n");MPI_Wait(&req,&st);printf("Process 0: Send completed.\n");}
 else{printf("Process 1: Starting non-blocking receive.\n");MPI_Irecv(received,100,MPI_CHAR,0,7,MPI_COMM_WORLD,&req);printf("Process 1: Doing other work while message is in transit...\n");MPI_Wait(&req,&st);printf("Process 1: Receive completed. Message: %s\n",received);}
 MPI_Finalize();return 0;
}
