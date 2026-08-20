// Program 10 - Search for a value in an array (Linear Search)
// Interactive: user enters size N, elements, then the value to search

#include <stdio.h>

int main() {
    int n, i, key, found = 0;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter value to search: ");
    scanf("%d", &key);

    for (i = 0; i < n; i++) {
        if (arr[i] == key) {
            printf("Found %d at position %d\n", key, i + 1);
            found = 1;
        }
    }

    if (!found)
        printf("%d not found in the array.\n", key);

    return 0;
}
