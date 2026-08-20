#include <stdio.h>
#include <omp.h>

int main() {

    #pragma omp parallel for schedule(dynamic, 1)
    for (int i = 0; i < 100; i++) {
        printf("Hello World - Iteration %d - Thread %d\n",
               i + 1, omp_get_thread_num());
    }

    return 0;
}
