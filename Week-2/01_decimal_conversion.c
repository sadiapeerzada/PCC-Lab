#include <stdio.h>

int main() {
    int n, binary[32], i = 0, temp;

    printf("Enter a decimal number: ");
    scanf("%d", &n);

    printf("Binary      : ");
    temp = n;

    if (temp == 0) {
        printf("0");
    } else {
        while (temp > 0) {
            binary[i++] = temp % 2;
            temp /= 2;
        }

        while (i > 0)
            printf("%d", binary[--i]);
    }

    printf("\nOctal       : %o", n);
    printf("\nHexadecimal : %X\n", n);

    return 0;
}
