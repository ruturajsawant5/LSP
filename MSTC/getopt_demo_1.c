#include <stdio.h> 
#include <stdlib.h> 
#include <getopt.h> 

#define TRUE 1 
#define FALSE 0 

void help(void); 
void version(void); 

int main(int argc, char* argv[]){
    int ret; 
    int flag=FALSE; 
    int a_flag=FALSE; 
    int b_flag=FALSE; 
    int h_flag=FALSE; 
    int v_flag=FALSE; 

    if(argc == 1){
        help(); 
        exit(EXIT_SUCCESS); 
    }

    while((ret = getopt(argc, argv, "hvab")) != -1){
        flag = TRUE; 
        switch((char)ret){
            case 'h':
                h_flag = TRUE; 
                help(); 
                break; 
            case 'v': 
                v_flag = TRUE; 
                version(); 
                break; 
            case 'a': 
                a_flag = TRUE; 
                break;  
            case 'b': 
                b_flag = TRUE; 
                break; 
            default: 
                help(); 
                exit(EXIT_FAILURE); 
        }
    }

    if(!flag){
        help(); 
        exit(EXIT_FAILURE); 
    }

    if(h_flag)
        puts("-h was given"); 

    if(v_flag)
        puts("-v was given"); 

    if(a_flag)
        puts("-a was given"); 

    if(b_flag)
        puts("-b was given"); 

    exit(EXIT_SUCCESS); 
}

void help(void){
    char* str_help = "./app [-h/-v]\n\
-h : for printing help\n\
-v : for printing version"; 
    puts(str_help); 
}

void version(void){
    puts("0.1"); 
}