#include <stdio.h>
#include <omp.h>

int power(int base, int exponent) {
    int result = 1;

    for (int i = 0; i < exponent; i++)
        result *= base;

    return result;
}

int isArmstrong(int n) {
    int original = n;
    int temp = n;
    int digits = 0;
    int sum = 0;

    if (n == 0)
        return 1;

    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    temp = n;

    while (temp != 0) {
        int digit = temp % 10;
        sum += power(digit, digits);
        temp /= 10;
    }

    return sum == original;
}

int main() {
    int num[20];

    printf("Enter 20 integers:\n");

    for (int i = 0; i < 20; i++)
        scanf("%d", &num[i]);

    printf("\nResults:\n");

    #pragma omp parallel for
    for (int i = 0; i < 20; i++) {
        if (isArmstrong(num[i]))
            printf("%d is an Armstrong number\n", num[i]);
        else
            printf("%d is not an Armstrong number\n", num[i]);
    }

    return 0;
}
