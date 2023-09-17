Compile the application.c
    gcc -g -c application.c -o application.o
Compile the dll.c
    gcc -g -c dll.c -o dll.o
Linking and create final executable :
    gcc -g application.o dll.o -o exe
Run the executable :
    ./exe

-g – GDB Flags 
-c – compile
-o – output file