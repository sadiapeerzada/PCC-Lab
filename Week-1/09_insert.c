#include <stdio.h>

int main() {
    int n, pos, value;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n + 1]; // extra space for the inserted element

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter position to insert (1 to %d): ", n + 1);
    scanf("%d", &pos);

    printf("Enter value to insert: ");
    scanf("%d", &value);

    // Shift elements to the right to make space
    for (int i = n; i >= pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos - 1] = value;
    n++; // array size increases by 1

    printf("Array after insertion:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}