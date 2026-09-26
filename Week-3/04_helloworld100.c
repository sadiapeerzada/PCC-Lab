#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    
    omp_set_num_threads(10);

    #pragma omp parallel for
    for (i = 0; i < 100; i++) {
        printf("Hello World!(%d)\n", omp_get_thread_num());
    }

    return 0;
}
