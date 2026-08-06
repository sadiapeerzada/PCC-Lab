// Program 9 - Insert a value at a given position in an array
// Interactive: user enters size N, the elements, then position + value to insert

#include <stdio.h>

int main() {
    int n, i, pos, val;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n + 1];   // one extra space for the new element

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter position to insert at (1 to %d): ", n + 1);
    scanf("%d", &pos);

    printf("Enter value to insert: ");
    scanf("%d", &val);

    if (pos < 1 || pos > n + 1) {
        printf("Invalid position!\n");
        return 0;
    }

    // shift everything after pos one step to the right
    for (i = n; i >= pos; i--)
        arr[i] = arr[i - 1];

    arr[pos - 1] = val;
    n = n + 1;

    printf("Array after insertion:\n");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
