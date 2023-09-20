#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int num = 100;
int main() {
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        printf("fork = %s\n", strerror(errno));
    }
    if (pid == 0) {
        printf("child before num = %d\n", num);
        num = 200;
        printf("child after num = %d\n", num);
    } else {
        sleep(5);
        printf("parent sleep num = %d\n", num);
    }
    exit(EXIT_SUCCESS);
}