#include <stdio.h>

void to_binary(int n) {
    int binary[32], i = 0;

    if (n == 0) {
        printf("Binary: 0\n");
        return;
    }

    while (n > 0) {
        binary[i] = n % 2;
        n = n / 2;
        i++;
    }

    printf("Binary: ");

    for (i = i - 1; i >= 0; i--) {
        printf("%d", binary[i]);
    }

    printf("\n");
}

int main() {
    int n, choice;

    printf("Enter a decimal number: ");
    scanf("%d", &n);

	to_binary(n);
    printf("Octal: %o\n", n);
    printf("Hexadecimal: %X\n", n);

    return 0;
}
