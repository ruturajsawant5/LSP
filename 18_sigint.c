#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep
void sigint_handler(int);
int main() {
    signal(SIGINT, sigint_handler);
    while (1) {
        puts("doing my work");
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}

void sigint_handler(int signum) {
    puts("ctrl+c pressed");
}