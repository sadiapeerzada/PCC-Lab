#include <stdio.h>

int main() {
    int num[20];

    printf("Enter 20 integers:\n");

    for (int i = 0; i < 20; i++)
        scanf("%d", &num[i]);

    printf("\nResults:\n");

    for (int i = 0; i < 20; i++) {
        if (num[i] % 2 == 0)
            printf("%d is Even\n", num[i]);
        else
            printf("%d is Odd\n", num[i]);
    }

    return 0;
}
