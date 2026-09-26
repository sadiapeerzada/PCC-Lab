#include <stdio.h>
#include <omp.h>
#define N 20

int main() {
	int i, id;
	int arr[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	id = omp_get_thread_num();

	#pragma omp parallel for
	for (i = 0; i < N; i++) {
		if (arr[i] % 2 == 0) {
			printf("Thread %d: %d is even.\n", id, arr[i]);
		}
		else printf("Thread %d: %d is odd.\n", id, arr[i]);
	}
	
	return 0;
}
