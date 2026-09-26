# include <stdio.h>

int main() {
	int i, n1, n2;

	printf("Enter the number of elements in array 1: ");
	scanf("%d", &n1);	
	printf("Enter the number of elements in array 2: ");
	scanf("%d", &n2);

	int arr1[n1], arr2[n2], arr3[n1 + n2];
	
	printf("Enter the elements of array 1: ");
	for (i = 0; i < n1; i++) {
		scanf("%d", &arr1[i]);
	}
	printf("Enter the elements of array 2: ");
	for (i = 0; i < n2; i++) {
		scanf("%d", &arr2[i]);
	}
	
	for(i = 0; i < n1 + n2; i++) {
		if (i < n1){
			arr3[i] = arr1[i];
		}
		
		else {
			arr3[i] = arr2[i - n1];
		}
	}
	
	printf("The merged array is:\n");
	for (i = 0; i < n1 + n2; i++) {
		printf("%d ", arr3[i]);
	}
	printf("\n");
	
}
