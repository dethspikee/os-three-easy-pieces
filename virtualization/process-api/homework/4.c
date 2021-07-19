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
        printf("Child process\n");
    } else {
        wait(NULL);
        printf("Parent process\n");
    }
    return EXIT_SUCCESS;
}
