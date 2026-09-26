#include <stdio.h>
#include <omp.h>

int main() {
	int sum = 0;

	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		sum += id;

		printf("Thread %d adding...\n", id);
	}
	printf("Final Sum = %d\n", sum);

	return 0;
}
