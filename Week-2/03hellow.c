#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
	#pragma omp parallel 
	{
		printf("Hello, world!\n");
	}		
}

