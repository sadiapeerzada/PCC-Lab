#include <stdio.h>
#include <math.h>

int main() {
    double principal, rate, time;
    double simpleInterest, compoundInterest, compoundAmount;

    printf("Enter principal amount: ");
    scanf("%lf", &principal);

    printf("Enter rate of interest (in %%): ");
    scanf("%lf", &rate);

    printf("Enter time period (in years): ");
    scanf("%lf", &time);

    // Simple Interest = (P * R * T) / 100
    simpleInterest = (principal * rate * time) / 100;

    // Compound Interest = P * (1 + R/100)^T - P
    compoundInterest = (principal * pow((1 + rate / 100), time)) - principal;

    printf("\nSimple Interest   = %.2lf\n", simpleInterest);
    printf("Compound Interest = %.2lf\n", compoundInterest);

    return 0;
}