/*
   Make child process print first without calling wait() in the parent. 
   Solution proposed: use pipe()
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char *argv[]) {
    char *str = "Goodbye\n";
    int pipefd[2];
    pid_t cpid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        fprintf(stderr, "Error forking new process.\n");
        exit(EXIT_FAILURE);
    }

    if (cpid < 0) {
        fprintf(stderr, "Error forking child process.\n");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        close(pipefd[0]);
        write(STDOUT_FILENO, "Hello ", strlen("Hello "));
        write(pipefd[1], str, strlen(str));
        close(pipefd[1]);
    } else {
        char buffer;
        close(pipefd[1]);
        while((read(pipefd[0], &buffer, 1) > 0)) {
            write(STDOUT_FILENO, &buffer, 1);
        }
        close(pipefd[0]);
    }

    return EXIT_SUCCESS;
}
