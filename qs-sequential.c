#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>

#ifdef QSPARALLEL
#include "qs-parallel.h"
#define qsort qsort_parallel
#define VERSION "Parallel"
#else
#define VERSION "Sequential"
#endif

#define TYPE double

long long wall_clock_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1e6 + tv.tv_usec;
}

int less_than(const void* a, const void* b) {
    TYPE v1 = *(TYPE *)a;
    TYPE v2 = *(TYPE *)b;

    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}

int main(int argc, char* argv[]) {
    int i, N;
    long long start, end;

    if (argc != 2) {
        printf("Usage: ./quicksort-seq N\n");
        return -1;
    }

    srand48(time(NULL));
    N = atol(argv[1]);

    TYPE* array = malloc(sizeof(*array) * N);
    for (i = 0; i < N; i++)
        array[i] = drand48();

    start = wall_clock_time();
    qsort(array, N, sizeof(*array), less_than);
    end = wall_clock_time();

    printf("QuickSort %s: Array size = %d, Wall clock elapsed time = %ld\n", VERSION, N, (long) (end-start));

    free(array);

    return 0;
}
