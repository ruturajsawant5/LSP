gcc -g -c application.c -o application.o

gcc -g -c dll.c -o dll.o

gcc -g application.o dll.o -o exe

./exe
