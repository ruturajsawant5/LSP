# static library .a
```bash
gcc -c dll.c -o dll.o

gcc -c dll_util.c -o dll_util.o

ar rs libdll.a dll.o dll_util.o
```

# linking static lib
```bash
gcc -c application.c -o application.o

gcc application.o -o exe -L . -ldll

./exe
```

#dynamic library .so
```bash
gcc -c -fPIC dll.c -o dll.o

gcc -c -fPIC dll_util.c -o dll_util.o

gcc dll.o dll_util.o -shared -o libdll.so
```

#linking dynamic library
```bash
gcc -c application.c -o application.o

cp libdll.so /usr/lib

sudo ldconfig

gcc application.o -o exe -ldll

./exe
```