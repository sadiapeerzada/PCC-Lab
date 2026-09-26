#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    
    # pragma omp parallel for
    for (i = 0; i < 30; i++) {
        printf("Hello World!(%d)\n", omp_get_thread_num());
    }

    return 0;
}
