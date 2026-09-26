#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>
#define N 20

bool armstrong(int n);

int main() {
	int i;
	int arr[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 25, 100, 123, 153, 370, 371, 407, 9474};
	
	# pragma omp parallel for
	for(i = 0; i < N; i++) {
		if(armstrong(arr[i])) printf("from thread %d: %d is an aromstrong number.\n", omp_get_thread_num(), arr[i]);
		else printf("from thread %d: %d is not an aromstrong number.\n", omp_get_thread_num(), arr[i]);
	}
	
	return 0;
}

bool armstrong(int n) {
	int temp = n, digits = 0, sum = 0;
	
	while (temp != 0) {
		digits++;
		temp /= 10;
	}
	
	temp = n;
	while(temp != 0) {
		sum = sum + pow(temp % 10, digits);
		temp /= 10;
	}
	
	return sum == n;
}
