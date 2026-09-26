#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define N 20

bool armstrong(int n);

int main() {
	int i;
	int arr[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 25, 100, 123, 153, 370, 371, 407, 9474};
	
	for (i = 0; i < N; i++) {
		if (armstrong(arr[i])) printf("%d is an aromstrong number.\n", arr[i]);
		else printf("%d is not an aromstrong number.\n", arr[i]);
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
	
	if (sum == n) return true;
	
	return false;
}

