#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
#define BUFFER_SIZE 4096
    static char buffer[BUFFER_SIZE];
    ssize_t read_bytes, written_bytes;

    while ((read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        written_bytes = write(STDOUT_FILENO, buffer, read_bytes);
    }

    exit(EXIT_SUCCESS);
}
