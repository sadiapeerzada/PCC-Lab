#include <stdio.h>
#include <omp.h>

int main() {

    #pragma omp parallel for
    for (int i = 0; i < 30; i++) {
        printf("Hello World\n");
    }

    return 0;
}
