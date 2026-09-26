#include <stdio.h>

int isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int start, end;

    printf("Enter the starting range: ");
    scanf("%d", &start);

    printf("Enter the ending range: ");
    scanf("%d", &end);

    printf("\nPrime numbers between %d and %d:\n", start, end);

    for (int i = start; i <= end; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }

    printf("\n");

    return 0;
}