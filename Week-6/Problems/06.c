#include <stdio.h>
#include <omp.h>

int main() {
	char* words[] = {"apple", "banana", "orange", "grape", "kiwi", "melon", "apricot"};
	char target = 'a';
	int count = 0, i, j;
	
	int n = sizeof(words) / sizeof(words[0]);
	
	#pragma omp parallel for
	for (i = 0; i < n; i++) {
		for (j = 0; words[i][j] != '\0'; j++) {
			if (words[i][j] == target) {
				#pragma omp atomic
				count++;
			}
		}
	}
	printf("Total '%c' occurences: %d.\n", target, count);
	
	return 0;
}
