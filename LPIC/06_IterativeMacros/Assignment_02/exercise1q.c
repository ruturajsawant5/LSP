#include <stdio.h>
#include <stdlib.h>

#define ITERATE_ARRAY_BEGIN(arrptr, array_size, start_index, scansize, out_index)  \
    for(int _i = start_index; _i < (start_index + scansize); _i++)                 \
    {                                                                              \
        out_index = _i % array_size;                                                            \
    

#define ITERATE_ARRAY_END }

int
main(int argc, char **argv){

    unsigned int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    unsigned int i;

    ITERATE_ARRAY_BEGIN(arr, 10, 5, 10, i) {
        printf("arr[%u] = %u\n", i, arr[i]);
    } ITERATE_ARRAY_END;

    return 0;
}