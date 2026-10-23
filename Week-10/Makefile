CC = gcc
CFLAGS = -O2 -Wall -Wextra -fopenmp
PROGRAMS = bitonic_sort gauss_seidel gauss_seidel_parallel compare_solvers

all: $(PROGRAMS)

bitonic_sort: bitonic_sort.c
	$(CC) $(CFLAGS) $< -o $@

gauss_seidel: gauss_seidel.c
	$(CC) $(CFLAGS) $< -lm -o $@

gauss_seidel_parallel: gauss_seidel_parallel.c
	$(CC) $(CFLAGS) $< -lm -o $@

compare_solvers: compare_solvers.c
	$(CC) $(CFLAGS) $< -lm -o $@

clean:
	rm -f $(PROGRAMS)

.PHONY: all clean
