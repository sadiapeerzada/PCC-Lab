// Program 6 - Print all prime numbers between two given numbers

#include <stdio.h>

int main() {
    int low, high, i, j, isPrime;

    printf("Enter lower limit: ");
    scanf("%d", &low);
    printf("Enter upper limit: ");
    scanf("%d", &high);

    printf("Prime numbers between %d and %d:\n", low, high);

    for (i = low; i <= high; i++) {
        if (i < 2)
            continue;

        isPrime = 1;
        for (j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        }

        if (isPrime == 1)
            printf("%d ", i);
    }
    printf("\n");

    return 0;
}
