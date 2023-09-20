#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    pid_t pid;
    int exit_status;
    pid = fork();

    if (pid == 0) {
        printf("child pid=%d getppid=%d\n", getpid(), getppid());

    } else {
        printf("parent pid=%d getppid=%d\n", getpid(), getppid());
        wait(&exit_status);
    }
    exit(EXIT_SUCCESS);
}