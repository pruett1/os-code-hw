#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Expected arguments for: number of pages to touch and number of trials");
        return 0;
    }

    int NUM_PAGES = atoi(argv[1]);
    int NUM_TRIALS = atoi(argv[2]);

    long PAGE_SIZE = sysconf(_SC_PAGESIZE);

    long jump = PAGE_SIZE / sizeof(int);

    int* a = malloc(NUM_PAGES * PAGE_SIZE);

    if (a == NULL) {
        printf("malloc failed");
        return 0;
    }

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int trial = 0; trial < NUM_TRIALS; ++trial) {
        
        for (int i = 0; i < NUM_PAGES * jump; i += jump) {
            a[i] += 1;
        }

    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    int64_t elapsed = (int64_t)(end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);

    printf("%.3f\n", (double)elapsed / (double)(NUM_TRIALS * NUM_PAGES));
    free(a);
}