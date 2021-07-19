#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void) {
    pid_t cpid;

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (cpid == 0) {
        char *arguments[2];
        arguments[0] = "ls";
        arguments[1] = NULL;
        execvp(arguments[0], arguments);
    } else {
        wait(NULL);
        printf("Finishing parent process.\n");
    }

    return EXIT_SUCCESS;
}
