#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
int main(int argc,char **argv){
 int rank,size;long long local_hits=0,global_hits=0,total_points=1000000,local_points;
 double start,elapsed,global_elapsed,pi;
 MPI_Init(&argc,&argv);MPI_Comm_rank(MPI_COMM_WORLD,&rank);MPI_Comm_size(MPI_COMM_WORLD,&size);
 if(argc>1){char *end;long long v=strtoll(argv[1],&end,10);if(*end||v<=0){if(rank==0)fprintf(stderr,"Points must be a positive integer.\n");MPI_Finalize();return 1;}total_points=v;}
 local_points=total_points/size+(rank<total_points%size);
 unsigned int seed=(unsigned int)time(NULL)^(unsigned int)(rank*2654435761u);
 start=MPI_Wtime();
 for(long long i=0;i<local_points;i++){double x=(double)rand_r(&seed)/((double)RAND_MAX+1.0);double y=(double)rand_r(&seed)/((double)RAND_MAX+1.0);if(x*x+y*y<=1.0)local_hits++;}
 MPI_Reduce(&local_hits,&global_hits,1,MPI_LONG_LONG_INT,MPI_SUM,0,MPI_COMM_WORLD);
 elapsed=MPI_Wtime()-start;MPI_Reduce(&elapsed,&global_elapsed,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
 if(rank==0){pi=4.0*(double)global_hits/(double)total_points;printf("Total points: %lld\nEstimated Pi: %.6f\nExecution Time: %.6f seconds\n",total_points,pi,global_elapsed);}
 printf("Process %d local hits: %lld\n",rank,local_hits);
 MPI_Finalize();return 0;
}
