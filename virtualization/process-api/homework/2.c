/*
   Write a program that opens a file (with the open() system call)
   and then calls fork() to create a new process. Can both the child
   and parent access the file descriptor returned by open()? What 
   happens when they are writing to the file concurrently, i.e., at
   the same time?
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>


int main(void) {
    int fd = open("test.txt", O_RDWR | O_APPEND, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Error forking child process.\n");
        exit(EXIT_FAILURE);
    }
    if (rc == 0) {
        write(fd, "damian", 6);
    } else {
        write(fd, "tabor", 5);
    }
    close(fd);
    return EXIT_SUCCESS;
}
