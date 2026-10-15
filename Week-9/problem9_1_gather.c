#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define LOCAL_N 3
int main(int argc,char **argv){
 int rank,size,local[LOCAL_N],*all=NULL;MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);MPI_Comm_size(MPI_COMM_WORLD,&size);
 for(int i=0;i<LOCAL_N;i++)local[i]=rank*10+i;
 printf("Process %d local: %d %d %d\n",rank,local[0],local[1],local[2]);
 if(rank==0){all=malloc((size_t)size*LOCAL_N*sizeof(int));if(!all){fprintf(stderr,"Allocation failed\n");MPI_Abort(MPI_COMM_WORLD,1);}}
 MPI_Gather(local,LOCAL_N,MPI_INT,all,LOCAL_N,MPI_INT,0,MPI_COMM_WORLD);
 if(rank==0){printf("Process 0 gathered array:");for(int i=0;i<size*LOCAL_N;i++)printf(" %d",all[i]);puts("");free(all);}
 MPI_Finalize();return 0;
}
