#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 2

void help(void);
void version(void);

int main(int argc, char *argv[]) {
    int ret;
    int flag = FALSE;
    char *source_path = NULL;
    char *dest_path = NULL;

    if (argc == 1) {
        help();
        exit(EXIT_FAILURE);
    }

    /*
        getopt will parse command line arguments.
        hv is list of valid options
        return -1 if argv endd
    */
    while ((ret = getopt(argc, argv, "hvs:d:")) != -1) {
        flag = TRUE;

        switch ((char)ret) {
        case 'h':
            help();
            break;

        case 'v':
            version();
            break;

        case 's':
            source_path = optarg;
            puts(source_path);
            break;
        case 'd':
            dest_path = optarg;
            puts(dest_path);
            break;

        default:
            help();
            exit(EXIT_FAILURE);
        }
    }

    if (!flag) {
        help();
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

void help(void) {
    char *str_help = "./app [-h/-v]\n\
-h : for printing help\n\
-v : for printing version";
    puts(str_help);
}

void version(void) {
    puts("0.1");
}