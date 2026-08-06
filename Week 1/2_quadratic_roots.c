// Program 2 - Find the roots of a quadratic equation ax^2 + bx + c = 0
// Three cases depending on the discriminant (b^2 - 4ac)

#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c, d, r1, r2, real, imag;

    printf("Enter a, b, c: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a == 0) {
        printf("Not a quadratic equation, 'a' can't be 0.\n");
        return 0;
    }

    d = b * b - 4 * a * c;   // discriminant

    if (d > 0) {
        r1 = (-b + sqrt(d)) / (2 * a);
        r2 = (-b - sqrt(d)) / (2 * a);
        printf("Roots are real and different\n");
        printf("root1 = %.2lf\nroot2 = %.2lf\n", r1, r2);
    }
    else if (d == 0) {
        r1 = -b / (2 * a);
        printf("Roots are real and equal\n");
        printf("root1 = root2 = %.2lf\n", r1);
    }
    else {
        real = -b / (2 * a);
        imag = sqrt(-d) / (2 * a);
        printf("Roots are complex\n");
        printf("root1 = %.2lf + %.2lfi\n", real, imag);
        printf("root2 = %.2lf - %.2lfi\n", real, imag);
    }

    return 0;
}
