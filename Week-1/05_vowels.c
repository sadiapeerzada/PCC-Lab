#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
    printf("Enter an alphabet: ");
    scanf("%c", &ch);

    if (!isalpha(ch)) {
        printf("%c is not a valid alphabet.\n", ch);
        return 0;
    }

    switch (tolower(ch)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            printf("%c is a vowel.\n", ch);
            break;
        default:
            printf("%c is a consonant.\n", ch);
    }

    return 0;
}