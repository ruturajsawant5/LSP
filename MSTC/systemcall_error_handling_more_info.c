#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <fcntl.h> 

int main(void){
    int fd; 

    const char* f_path_1 = "/home/yogeshwar/LALLALA/hello.c"; 
    const char* f_path_2 = "/etc/passwd"; 

    fd = open(f_path_1, O_RDWR | O_CREAT | O_TRUNC, 
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
    if(fd == -1){
        printf("%s:%d:open:%s:%s\n", __FILE__, __LINE__, f_path_1, strerror(errno)); 
    }

    fd = open(f_path_2, O_RDWR); 
    if(fd == -1){
        printf("%s:%d:open:%s:%s\n", __FILE__, __LINE__, f_path_2, strerror(errno)); 
    }

    exit(EXIT_SUCCESS); 
}
