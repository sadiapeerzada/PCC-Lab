#include <stdio.h>
#include <omp.h>

int main() {
	int i;
	
	printf("Serial part of the program.\n");
	
	#pragma omp parallel for
	for (i = 0; i < 10; i++) {
		printf("Iteration %d from thread %d\n", i, omp_get_thread_num());
	}
	
	printf("Back to serial part.\n");
	
	return 0;
}

