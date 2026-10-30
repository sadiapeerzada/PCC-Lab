CC=gcc
MPICC=mpicc
all: quicksort_omp mergesort_omp mergesort_mpi
quicksort_omp: quicksort_omp.c
	$(CC) -O2 -fopenmp $< -o $@
mergesort_omp: mergesort_omp.c
	$(CC) -O2 -fopenmp $< -o $@
mergesort_mpi: mergesort_mpi.c
	$(MPICC) -O2 $< -o $@
clean:
	rm -f quicksort_omp mergesort_omp mergesort_mpi
