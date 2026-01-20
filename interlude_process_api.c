#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

/* //Problem 1 
int main(int argc, char* argv[]) {
    int x = 100;
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process
        printf("Child Process: \n");
        printf("x: %d\n", x);
        x += 50;
        printf("x after mod: %d\n", x);
    }
    else {
        // Parent process
        printf("Parent Process:\n");
        printf("Child PID: %d\n", pid);
        printf("x: %d\n", x);
        x += 20;
        printf("x after mod: %d\n", x);
    }
} */

/* //Problem 2
int main(int argc, char* argv[]) {
    // redirect output to a file
    close(STDOUT_FILENO);
    int fd = open("interlude_process_api_output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd < 0) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("Child Process: \n");
    }
    else {
        printf("Parent Process:\n");
    }
} */

/* //Problem 3
//with wait
int main(int argc, char* argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("Hello \n");
    }
    else {
        wait(NULL);
        printf("Goodbye \n");
    }
}

//without wait
int main(int argc, char* argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        close(fd[0]); //close unused read end
        printf("Hello \n");
        fflush(stdout); //ensure "Hello" is printed before writing to pipe
        write(fd[1], "done", 4); //signal parent that child is done
        close(fd[1]); //close write end
    }
    else {
        close(fd[1]); //close unused write end
        char buffer[5];
        read(fd[0], buffer, 4); //block until child signals completion
        printf("Goodbye \n");
        close(fd[0]); //close read end
    }
} */

/* //Problem 4
// //execl
// int main(int argc, char* argv[]) {
//     pid_t pid = fork();

//     if (pid < 0) {
//         perror("Fork failed");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid == 0) {
//         execl("/bin/ls", "ls", NULL); // only have ls arg (null terminated list)
//         perror("execl failed");
//         exit(EXIT_FAILURE);
//     }
//     else {
//         wait(NULL);
//         printf("Child process completed\n");
//     }
// }

// //execle
// int main(int argc, char* argv[]) {
//     pid_t pid = fork();

//     if (pid < 0) {
//         perror("Fork failed");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid == 0) {
//         execle("/bin/ls", "ls", NULL, NULL); // first null terminates arg list, second null terminates envp
//         perror("execle failed");
//         exit(EXIT_FAILURE);
//     }
//     else {
//         wait(NULL);
//         printf("Child process completed\n");
//     }
// }

// //execlp
// int main(int argc, char* argv[]) {
//     pid_t pid = fork();

//     if (pid < 0) {
//         perror("Fork failed");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid == 0) {
//         execlp("ls", "ls", NULL); // searches PATH for ls
//         perror("execl failed");
//         exit(EXIT_FAILURE);
//     }
//     else {
//         wait(NULL);
//         printf("Child process completed\n");
//     }
// }

// //execv
// int main(int argc, char* argv[]) {
//     pid_t pid = fork();

//     if (pid < 0) {
//         perror("Fork failed");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid == 0) {
//         char *args[] = {"ls", NULL};
//         execv("/bin/ls", args);
//         perror("execv failed");
//         exit(EXIT_FAILURE);
//     }
//     else {
//         wait(NULL);
//         printf("Child process completed\n");
//     }
// }

//execvp
int main(int argc, char* argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        char *args[] = {"ls", NULL};
        execvp("ls", args); // searches PATH for ls
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    else {
        wait(NULL);
        printf("Child process completed\n");
    }
} */

/* //Problem 5
// //wait in parent
// int main(int argc, char* argv[]) {
//     pid_t pid = fork();

//     if (pid < 0) {
//         perror("Fork failed");
//         exit(EXIT_FAILURE);
//     }
//     else if (pid == 0) {
//         printf("Child Process PID: %d\n", getpid());
//     }
//     else {
//         int status = wait(NULL);
//         printf("Child with PID %d completed\n", status);
//     }
// }

//wait in child
int main(int argc, char* argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        int status = wait(NULL);
        printf("Parent with PID %d completed\n", status);
    }
    else {
        wait(NULL);
        printf("Parent Process PID: %d\n", getpid());
    }
}*/

/* //Problem 6
// //wait in parent
// int main(int argc, char* argv[]) {
//     pid_t parent_pid = getpid();
//     pid_t f = fork();

//     if (f < 0) {
//         perror("Fork failed");
//         exit(EXIT_FAILURE);
//     }
//     else if (f == 0) {
//         printf("Child process PID: %d\n", getpid());
//     }
//     else {
//         waitpid(f, NULL, 0);
//         printf("Parent process PID: %d\n", parent_pid);
//     }
// }

//wait in child
int main(int argc, char* argv[]) {
    pid_t parent_pid = getpid();
    pid_t f = fork();

    if (f < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (f == 0) {
        waitpid(parent_pid, NULL, 0);
        printf("Child process PID: %d\n", getpid());
    }
    else {
        printf("Parent process PID: %d\n", parent_pid);
    }
} */

/* //Problem 7
int main(int argc, char* argv[]) {
    pid_t f = fork();

    if (f < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);    
    }
    else if (f == 0) {
        close(STDOUT_FILENO);
        printf("Should not print this\n");
    }
    else {
        wait(NULL);
        printf("This should print\n");
    }
} */

//Problem 8
int main(int argc, char* argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t f1 = fork();
    pid_t f2;
    if (f1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (f1 > 0) { //create second child in parent but not in first child
        f2 = fork(); 
        if (f2 < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    if (f1 == 0) {
        close(fd[0]); //close unused read end
        printf("Hi from child 1: %d\t", getpid());
        fflush(stdout);
        write(fd[1], "d", 1); //signal child 2
    }
    else if (f2 == 0) {
        close(fd[1]); //close unused write
        char buffer[2];
        read(fd[0], buffer, 1); //block until f1 signals
        printf("Hi child 1. Im child 2: %d\n", getpid());
        close(fd[0]);
    }
    else {
        wait(NULL);
        wait(NULL);
    }
}