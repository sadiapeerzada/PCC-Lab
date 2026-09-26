#include <stdio.h>
#include <omp.h>
 
int main() {
	int value, thread_id, total_threads;
	
	omp_set_num_threads(4);
	#pragma omp parallel private(value, thread_id)
	{
		thread_id = omp_get_thread_num();
		total_threads = omp_get_num_threads();
		
		value = thread_id * 10;
		printf("Thread %d calculated value %d.\n", thread_id, value);
		
		#pragma omp barrier		
		printf("Thread %d's value is %d, and total active threads are %d.\n", thread_id, value, total_threads);
	}
	
	return 0;
}
