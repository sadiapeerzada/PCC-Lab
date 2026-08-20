#include <stdio.h>
#include <omp.h>

int main() {
    int n;
    unsigned long long factorial = 1;

    printf("Enter an integer: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Factorial is not defined for negative integers.\n");
        return 0;
    }

    #pragma omp parallel for reduction(*:factorial)
    for (int i = 1; i <= n; i++)
        factorial *= i;

    printf("Factorial of %d = %llu\n", n, factorial);

    return 0;
}
