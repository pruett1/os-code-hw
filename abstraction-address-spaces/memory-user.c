#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

long timeInMs(void) {
    struct timespec timeVal;
    clock_gettime(CLOCK_MONOTONIC, &timeVal);
    return (long)((timeVal.tv_sec)*1000L + (timeVal.tv_nsec) / 1000000L);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Expected arguments for: memory size of array in MB, time in seconds for program to stream through array");
        return 0;
    }

    printf("PID: %d\n", getpid());

    long mem_size = strtol(argv[1], NULL, 10);
    printf("mem_size: %ld mb\n", mem_size);
    mem_size *= 1024 * 1024;

    long time = strtol(argv[2], NULL, 10);
    printf("time run: %ld s\n", time);
    time *= 1000;

    int* arr = malloc(mem_size);
    size_t size = mem_size / sizeof(int);

    if (arr == NULL) {
        printf("malloc failed");
        return 0;
    }

    long start = timeInMs();

    while ( time > (timeInMs() - start) ) {
        for (size_t i = 0; i < size; i++){
            arr[i]++;
        }
    }

    free(arr);
    arr = NULL;
    return 0;
}