// Program 4 - Calculate Simple Interest and Compound Interest
// SI = (P*R*T)/100
// CI = P*(1+R/100)^T - P   (compounded yearly)

#include <stdio.h>
#include <math.h>

int main() {
    float p, r, t;
    float si, ci, amount;

    printf("Enter principal amount: ");
    scanf("%f", &p);
    printf("Enter rate of interest: ");
    scanf("%f", &r);
    printf("Enter time (in years): ");
    scanf("%f", &t);

    si = (p * r * t) / 100;

    amount = p * pow((1 + r / 100), t);
    ci = amount - p;

    printf("\nSimple Interest = %.2f\n", si);
    printf("Compound Interest = %.2f\n", ci);

    return 0;
}
