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
        execl("/usr/bin/ls", "ls", (char *) NULL);
    } else {
        wait(NULL);
        printf("Finishing parent process.\n");
    }

    return EXIT_SUCCESS;
}
