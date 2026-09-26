#include <stdio.h>
#include <omp.h>

int main() {
	#pragma omp parallel
	{
		printf("Thread %d is running on a system with %d processors.\n", omp_get_thread_num(), omp_get_num_procs());
	}
	
	return 0;
}

