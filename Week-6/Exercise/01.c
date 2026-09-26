#include <stdio.h>
#include <omp.h>

int global_var = 100; // Global variable is shared by default

int main() {
    int i = 10; // Shared by default within parallel region if not specified
    int j = 20; // Shared by default
    int k = 30; // Shared by default

#pragma omp parallel default(none) shared(i, global_var) private(j) // k is implicitly shared if not specified,buthere default(none) forces it
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: i (shared) = %d, global_var (shared) = %d\n", thread_id, i, global_var);
        printf("Thread %d: j (private) = %d (before modification)\n", thread_id, j);

        j = thread_id * 100; // Each thread modifies its private copy of j
        printf("Thread %d: j (private) = %d (after modification)\n", thread_id, j);

        // If a variable like 'k' was used without being declared private or shared,
        // with default(none), it would result in a compilation error.
        // For simplicity, we stick to i, j, global_var for this example.
    }
    
    printf("\nAfter parallel region:\n");
    printf("Main thread: i = %d, global_var = %d\n", i, global_var);
    // printf("Main thread: j = %d (value undefined after parallel region for private j)\n", j);
    // This would be problematic
    return 0;
}