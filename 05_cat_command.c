#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 2

int main(int argc, char *argv[]) {
    int fd = -1;
#define BUFFER_SIZE 4096
    static char buffer[BUFFER_SIZE];
    ssize_t read_bytes, written_bytes;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("open:%s:%s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((read_bytes = read(fd, buffer, BUFFER_SIZE)) > 0) {
        written_bytes = write(STDOUT_FILENO, buffer, read_bytes);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
