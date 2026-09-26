#include <stdio.h>
#include <omp.h>

int factorial(int n);

int main() {
    int n, i;
    long long fact = 1;

    printf("Enter a number to find its factorial: ");
    scanf("%d", &n);

	#pragma omp parallel for reduction(*:fact)
	for (i = 1; i <= n; i++) {
		fact = fact * i;
	}
	
    printf("Factorial of %d is %lld.\n", n, fact);

    return 0;
}

