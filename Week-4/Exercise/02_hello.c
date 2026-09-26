#include <stdio.h>
#include <omp.h>

int main(){
    omp_set_num_threads(5); // Set the desired number of threads

    #pragma omp parallel
    {
        printf("Hello from thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
    return 0;
}
