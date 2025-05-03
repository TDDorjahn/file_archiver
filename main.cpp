#include <stdio.h>
#include <string.h>
#include "sparse.hpp"

int main(int argc, char * argv[]) {

    printf("Code for executable.\n");

    struct buffer b;
    b.buf = (char *)"Hello";
    b.size = STRSIZE_BOUND;

    printf("buffer: %s, size: %zu\n", b.buf, b.size);

    printf("buffer: %s, size: %zu\n", b.buf, b.size);

    return 0;

}