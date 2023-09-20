#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

int main() {
    int sys_ret;
    struct rusage ru;
    sys_ret = getrusage(RUSAGE_SELF, &ru);
    if (sys_ret == -1) {
        printf("getrusage error + %s", strerror(errno));
    }
    printf("User CPU Time Used  = %ld.%06ld\n", ru.ru_utime.tv_sec,
           ru.ru_utime.tv_usec);
    printf("System CPU TImer Used = %ld.%06ld\n", ru.ru_stime.tv_sec,
           ru.ru_stime.tv_usec);

    printf("maximum resident set size = %lu\n", ru.ru_maxrss);
    printf("integral shared memory size = %lu\n", ru.ru_ixrss);
    printf("integral unshared data size = %lu\n", ru.ru_idrss);
    printf("integral unshared stack size= %lu\n", ru.ru_isrss);
    printf("page reclaims (soft page faults)= %lu\n", ru.ru_minflt);
    printf("page faults (hard page faults)= %lu\n", ru.ru_majflt);
    printf("swaps = %lu\n", ru.ru_nswap);
    printf("block input operations = %lu\n", ru.ru_inblock);
    printf("block output operations= %lu\n", ru.ru_oublock);
    printf("IPC messages sent= %lu\n", ru.ru_msgsnd);
    printf("IPC messages received= %lu\n", ru.ru_msgrcv);
    printf("signals received = %lu\n", ru.ru_nsignals);
    printf("volunntary context switches= %lu\n", ru.ru_nvcsw);
    printf("involunntary context switches = %lu\n", ru.ru_nivcsw);

    exit(EXIT_SUCCESS);
}