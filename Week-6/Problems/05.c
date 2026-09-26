#include <stdio.h>
#include <omp.h>

int main() {
	int i, counter = 0;
	
	#pragma omp parallel firstprivate(i) shared(counter)
	{
		#pragma omp for
		for(i = 0; i < 10000; i++) {
		counter++;
		
		printf("Thread %d: i = %d, counter modified.\n", omp_get_thread_num(), i);
		}
	}
	
	printf("Final counter value (incorrect): %d\n", counter);
	
	return 0;
}
 