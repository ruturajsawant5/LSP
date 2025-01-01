Compile the application.c
```bash
    gcc -g -c application.c -o application.o
```

Compile the dll.c
```bash 
    gcc -g -c dll.c -o dll.o
```

Linking and create final executable
```bash    
    gcc -g application.o dll.o -o exe
```

Run the executable :
```bash
    ./exe
```
Flags:
```bash
-g – GDB Flags

-c – compile

-o – output file
```

Preprocess a source file
```bash
gcc -E app.c -o app.i
```