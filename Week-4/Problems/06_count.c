# include<stdio.h>
# include<omp.h>

int main(){
	
	# pragma omp parallel
	{
		printf("I am thread %d of %d active threads\n", omp_get_thread_num(), omp_get_num_threads());
	}
}

