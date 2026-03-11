#include <stdlib.h>
#include <stdio.h>

// int main(int argc, char* argv[]) {
//     int *memleak = (int *) malloc(sizeof(int) * 100);
//     *memleak = 42;
//     memleak = NULL;
//     return 0;
// }

// int main() {
//     int* data = (int*) malloc(100);
//     data[100] = 0;
//     free(data);
//     return 0;
// }

int main() {
    int* data = (int*) malloc(100);
    free(data);
    printf("%d\n", data[50]);
    return 0;
}

// int main() {
//     int* data = (int*) malloc(100);
//     free(&data[50]);
//     return 0;
// }