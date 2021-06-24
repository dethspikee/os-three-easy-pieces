#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main(void) {
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        open("./output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

        char *myargs[3];
        myargs[0] = strdup("cat");
        myargs[1] = strdup("p4.c");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
    } else {
        int rc_wait = wait(NULL);
        printf("Closing parent...\n");
    }
    return 0;
}
