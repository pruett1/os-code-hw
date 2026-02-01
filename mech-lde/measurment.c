#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char* argv[]) {
    int ctop[2];
    if (pipe(ctop) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }
    int ptoc[2];
    if (pipe(ptoc) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    struct timespec tPs, tPe, tCs, tCe;
    long total_parent_time = 0;
    long total_child_time = 0;
    int num_iterations = 100000;

    printf("Measuring context switch time over %d iterations...\n", num_iterations);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { 
        close(ptoc[1]); // Close unused write end
        close(ctop[0]); // Close unused read end
        char buffer[2];
        for (int i = 0; i < num_iterations; i++) {
            clock_gettime(CLOCK_MONOTONIC, &tCs);
            write(ctop[1], "x", 1); // Signal parent
            read(ptoc[0], buffer, 1); //Wait for parent response
            clock_gettime(CLOCK_MONOTONIC, &tCe);
            long delta_usec = (tCe.tv_sec - tCs.tv_sec) * 1000000 + (tCe.tv_nsec - tCs.tv_nsec) / 1000;
            total_child_time += delta_usec;
        }
        close(ptoc[0]);
        close(ctop[1]);
        printf("Average Child Time: %f microseconds\n", total_child_time / (float)num_iterations / 2);
    }
    else {
        close(ptoc[0]); // Close unused read end
        close(ctop[1]); // Close unused write end
        char buffer[2];
        for (int i = 0; i < num_iterations; i++) {
            clock_gettime(CLOCK_MONOTONIC, &tPs);
            read(ctop[0], buffer, 1); // Wait for child signal
            write(ptoc[1], "y", 1); // Respond to child
            clock_gettime(CLOCK_MONOTONIC, &tPe);
            long delta_usec = (tPe.tv_sec - tPs.tv_sec) * 1000000 + (tPe.tv_nsec - tPs.tv_nsec) / 1000;
            total_parent_time += delta_usec;
        }
        close(ptoc[1]);
        close(ctop[0]);
        printf("Average Parent Time: %f microseconds\n", total_parent_time / (float)num_iterations / 2);
    }
}