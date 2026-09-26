#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
#define N 20

bool isPerfect(int n);
     
int main() {
     int i, id;
     int arr[N] = {4, 6, 12, 28, 36, 55, 72, 111, 246, 381, 412, 496, 528, 726, 984, 1020, 5368, 6248, 8128, 10496};
     id = omp_get_thread_num();
     
     # pragma omp parallel for
     for (i = 0; i < N; i++) {
         if (isPerfect(arr[i])) {
            printf("from thread %d: %d is a PERFECT number.\n", id, arr[i]);
         }
         else printf("from thread %d: %d is not a perfect number.\n", id, arr[i]);
     }
     
     return 0;
}

bool isPerfect(int n) {
     int i, sum = 0;
     
     for (i = 1; i < n; i++) {
         if (n % i == 0) sum += i;
     }
     
     return sum == n;
}
