#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


int main(int argc, char *argv[]) {
    char buffer[1] = {0};
    long int timer_start, timer_end;
    struct timeval time;

    gettimeofday(&time, NULL);
    timer_start = time.tv_usec;

    int i;
    for (i = 0; i < 10; i++) {
        read(0, buffer, 0);
    }

    gettimeofday(&time, NULL);
    timer_end = time.tv_usec;
    printf("%d System calls took: %ld microseconds\n", i, timer_end - timer_start);
    printf("On average each system call took: %.3lf microseconds\n", (timer_end - timer_start) / (float) i);

    return EXIT_SUCCESS;
}
