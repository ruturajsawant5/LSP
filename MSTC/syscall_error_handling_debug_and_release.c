#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <fcntl.h> 

int main(void){
    int fd;

    const char* f_path_1 = "/home/yogeshwar/LALA/hello.c"; 
    const char* f_path_2 = "/etc/passwd"; 

    fd = open(f_path_1, O_RDONLY); 
    if(fd == -1){
        #ifndef DEBUG 
        printf("open:%s:%s\n", f_path_1, strerror(errno)); 
        #else 
        printf("%s:%d:open:%s:%s\n", __FILE__, __LINE__, f_path_1, 
                strerror(errno)); 
        #endif 
    }

    fd = open(f_path_2, O_RDWR); 
    if(fd == -1){
        #ifndef DEBUG 
        printf("open:%s:%s\n", f_path_2,  strerror(errno)); 
        #else 
        printf("%s:%d:open:%s:%s\n", __FILE__, __LINE__, f_path_1, 
                strerror(errno)); 
        #endif 
    }

    exit(EXIT_SUCCESS); 
} 

