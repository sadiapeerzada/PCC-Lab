#include <stdio.h>

int main() {
    int n, key, found = 0;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter value to search: ");
    scanf("%d", &key);

    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            printf("Value %d found at position %d (index %d).\n", key, i + 1, i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Value %d not found in the array.\n", key);
    }

    return 0;
}