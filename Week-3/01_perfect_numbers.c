#include <stdio.h>

int isPerfect(int n) {
    int sum = 0;

    if (n <= 1)
        return 0;

    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0)
            sum += i;
    }

    return sum == n;
}

int main() {
    int num[20];

    printf("Enter 20 integers:\n");

    for (int i = 0; i < 20; i++)
        scanf("%d", &num[i]);

    printf("\nResults:\n");

    for (int i = 0; i < 20; i++) {
        if (isPerfect(num[i]))
            printf("%d is a Perfect number\n", num[i]);
        else
            printf("%d is not a Perfect number\n", num[i]);
    }

    return 0;
}
