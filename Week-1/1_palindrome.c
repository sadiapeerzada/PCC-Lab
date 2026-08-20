// Program 1 - Check if a number is a palindrome
// A palindrome number reads the same forwards and backwards, e.g. 121, 1331

#include <stdio.h>

int main() {
    long num, temp, rev = 0, rem;

    printf("Enter an integer: ");
    scanf("%ld", &num);

    temp = num;

    // negative numbers - just check the digits, ignore the sign
    if (temp < 0)
        temp = -temp;

    // reverse the number digit by digit
    while (temp != 0) {
        rem = temp % 10;
        rev = rev * 10 + rem;
        temp = temp / 10;
    }

    if (num == rev || -num == rev)
        printf("%ld is a palindrome number.\n", num);
    else
        printf("%ld is NOT a palindrome number.\n", num);

    return 0;
}
