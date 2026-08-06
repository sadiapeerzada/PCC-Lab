// Program 7 - Find the LCM and HCF of two numbers

#include <stdio.h>

int main() {
    int n1, n2, a, b, temp, hcf, lcm;

    printf("Enter two numbers: ");
    scanf("%d %d", &n1, &n2);

    a = n1;
    b = n2;

    // Euclidean algorithm for HCF
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    hcf = a;

    lcm = (n1 * n2) / hcf;

    printf("HCF = %d\n", hcf);
    printf("LCM = %d\n", lcm);

    return 0;
}
