#include <stdio.h>

int main() {
    int n1, n2;

    printf("Enter size of first array: ");
    scanf("%d", &n1);

    int a[n1];

    printf("Enter elements of first array:\n");
    for (int i = 0; i < n1; i++)
        scanf("%d", &a[i]);

    printf("Enter size of second array: ");
    scanf("%d", &n2);

    int b[n2], c[n1 + n2];

    printf("Enter elements of second array:\n");
    for (int i = 0; i < n2; i++)
        scanf("%d", &b[i]);

    for (int i = 0; i < n1; i++)
        c[i] = a[i];

    for (int i = 0; i < n2; i++)
        c[n1 + i] = b[i];

    printf("Merged array:\n");
    for (int i = 0; i < n1 + n2; i++)
        printf("%d ", c[i]);

    printf("\n");
    return 0;
}
