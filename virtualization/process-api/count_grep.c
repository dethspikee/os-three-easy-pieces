#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    pid_t cpid;
    int pipefd[2];
    //char buffer[4096];

    if (argc != 3) {
        fprintf(stderr, "Usage: <search term> <source file>\n");
        return EXIT_FAILURE;
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (cpid == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execl("/usr/bin/grep", "grep", "--color=always", argv[1], argv[2], (char *) NULL);
        perror("problem with exec call\n");
        return EXIT_FAILURE;
    } else {
        wait(NULL);
        char buffer;
        close(pipefd[1]);
        while (read(pipefd[0], &buffer, 1) > 0) {
            printf("%c", buffer);
        }
    }

    return EXIT_SUCCESS;
}
