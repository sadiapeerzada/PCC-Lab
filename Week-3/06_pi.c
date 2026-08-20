#include <stdio.h>

int main() {
    long long n;
    double sum = 0.0;
    double pi;

    printf("Enter number of terms: ");
    scanf("%lld", &n);

    for (long long i = 0; i < n; i++) {
        if (i % 2 == 0)
            sum += 1.0 / (2 * i + 1);
        else
            sum -= 1.0 / (2 * i + 1);
    }

    pi = 4.0 * sum;

    printf("Computed value of pi = %.15f\n", pi);

    return 0;
}
