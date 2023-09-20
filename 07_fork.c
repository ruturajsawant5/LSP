#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        printf("child pid returned by fork= %d\n", pid);
    } else {
        printf("parent pid returned by fork= %d\n", pid);
    }
    exit(EXIT_SUCCESS);
}