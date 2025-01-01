#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <getopt.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define TRUE 	1 
#define FALSE 	0 

void help(void); 
void version(void); 
void copy(const char* src_path, const char* dest_path); 

int main(int argc, char* argv[]){
	int ret; 
	char* src_path = NULL; 
	char* dest_path = NULL; 
	int flag = FALSE; 
	int src_flag = FALSE; 
	int dest_flag = FALSE; 

	while((ret = getopt(argc, argv, "hvs:d:")) != -1){
		flag = TRUE; 
		switch((char)ret){
			case 'h': 
				help(); 
				exit(EXIT_SUCCESS); 
			case 'v':
				version(); 
				exit(EXIT_SUCCESS); 
			case 's': 
				src_flag = TRUE; 
				src_path = optarg; 
				break; 
			case 'd': 
				dest_flag = TRUE; 
				dest_path = optarg; 
				break; 
			default: 
				help(); 
				exit(EXIT_SUCCESS); 
		}
	}

	if(!flag){
		help(); 
		exit(EXIT_FAILURE); 
	}

	if(src_flag != dest_flag){
		puts("Either source or destination path is missing"); 
		exit(EXIT_FAILURE); 
	}

	copy((const char*)src_path, (const char*)dest_path); 
	exit(EXIT_SUCCESS); 
}

void copy(const char* src_path, const char* dest_path){
	int src_fd=-1; 
	int dest_fd=-1; 
	#define BUFFER_SIZE 4096
	static char buffer[BUFFER_SIZE]; 
	ssize_t read_bytes, written_bytes; 

	src_fd = open(src_path, O_RDONLY); 
	if(src_fd == -1){
		printf("open:%s:%s\n", src_path, strerror(errno)); 
		exit(EXIT_FAILURE); 
	}

	dest_fd = open(dest_path,
					O_RDWR | O_CREAT | O_TRUNC, 
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
	if(dest_fd == -1){
		printf("open:%s:%s\n", dest_path, strerror(errno)); 
		exit(EXIT_FAILURE); 
	}

	while((read_bytes = read(src_fd, buffer, BUFFER_SIZE)) > 0){
		written_bytes = write(dest_fd, buffer, read_bytes); 
		if(written_bytes != read_bytes){
			printf("write:%s:%s\n", dest_path, strerror(errno)); 
			exit(EXIT_FAILURE); 
		}
	}
	if(read_bytes == -1){
		printf("read:%s:%s\n", src_path, strerror(errno)); 
		exit(EXIT_FAILURE); 
	}

	if(close(src_fd) == -1){
		printf("close:%s:%s\n", src_path, strerror(errno)); 
		exit(EXIT_FAILURE); 
	}

	if(close(dest_fd) == -1){
		printf("close:%s:%s\n", dest_path, strerror(errno)); 
		exit(EXIT_FAILURE); 
	}
}

void help(void){
	static const char* help_string = "cpacp -h\n\
cpacp -v\n\
cpacp -s src_path -d dest_path\n\
-h	: prints help\n\
-v 	: prints version\n\
-s 	: specifies source path\n\
-d 	: specifies destination path"; 
	puts(help_string); 
}

void version(void){
	puts("0.1"); 
}
