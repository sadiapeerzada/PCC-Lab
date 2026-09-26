#include <stdio.h>
#include <omp.h>

int main() {
    int x = 10;
    int y = 20;
    int z = 0; // Will be used with lastprivate, initialized here for clarity

    printf("Before parallel region: x = %d, y = %d, z = %d\n", x, y, z);

#pragma omp parallel for firstprivate(x) lastprivate(y, z)
    for (int i = 0; i < 5; i++) {
        int thread_id = omp_get_thread_num();
        printf("Thread %d, Iteration %d: x (firstprivate) = %d\n", thread_id, i, x);
        x = x + 1;  // Each thread increments its own copy of x
        y = i * 10; // Each thread sets its own copy of y
        z = i;      // Each thread sets its own copy of z; last one wins for lastprivate

        printf("Thread %d, Iteration %d: x (modified) = %d, y (modified) = %d, z (modified) = % d\n ", thread_id, i,x,y,z);
    }

    printf("\nAfter parallel region: x = %d (unchanged), y = %d (lastprivate), z = %d (lastprivate)\n", x, y, z);
    
    return 0;
}