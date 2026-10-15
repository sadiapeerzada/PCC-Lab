#include <stdio.h>
#include <omp.h>
int main(void) {
    #pragma omp parallel
    {
        int tid=omp_get_thread_num();
        printf("Thread %d: Starting parallel region.\n",tid);
        #pragma omp sections
        {
            #pragma omp section
            printf("Task A executed by thread %d\n",omp_get_thread_num());
            #pragma omp section
            printf("Task B executed by thread %d\n",omp_get_thread_num());
            #pragma omp section
            printf("Task C executed by thread %d\n",omp_get_thread_num());
        }
        #pragma omp single
        printf("Thread %d: Only one thread executes this single block.\n",omp_get_thread_num());
        printf("Thread %d: After single block.\n",tid);
    }
    return 0;
}
