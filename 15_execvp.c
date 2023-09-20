#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    //strerror
#include <sys/types.h> //pid_t
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
    static char *ls_basename = "ls";
    static char *ls_command_line[] = {"ls", "-l", "/", NULL};

    pid_t pid;
    int exit_status;
    int sys_ret;

    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "fork=%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        sys_ret = execvp(ls_basename, ls_command_line);
        if (sys_ret == -1) {
            fprintf(stderr, "execve=%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    } else {
        wait(&exit_status);
        puts("Parent Terminating");
    }
    exit(EXIT_SUCCESS);
}