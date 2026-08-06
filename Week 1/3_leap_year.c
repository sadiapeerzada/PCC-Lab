// Program 3 - Check if the given year is a leap year
// Rule: divisible by 4, but not by 100 unless also divisible by 400

#include <stdio.h>

int main() {
    int year;

    printf("Enter a year: ");
    scanf("%d", &year);

    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                printf("%d is a leap year.\n", year);
            else
                printf("%d is NOT a leap year.\n", year);
        } else {
            printf("%d is a leap year.\n", year);
        }
    } else {
        printf("%d is NOT a leap year.\n", year);
    }

    return 0;
}
