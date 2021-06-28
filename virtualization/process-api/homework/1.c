/*
 Write a program that calls fork(). Before calling fork(),
 have the main process access a variable (e.g., x) and set
 its value to something (e.g., 100). What value is the
 variable when both the child and parent change the value
 of x?
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void) {
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Error when forking new child process.\n");
        return 1;
    }
    if (rc == 0) {
        x = 200;
        printf("x: %d\n", x);
    } else {
        x = 150;
        printf("x: %d\n", x);
    }

    return 0;
}
