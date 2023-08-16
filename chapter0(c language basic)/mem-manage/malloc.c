#include <stdio.h>
#include <stdlib.h>
#include "chapter1/hello_client.c"

int main(int argc, char const *argv[])
{
    // allocate a block memory used to store an array with 10 elements
    int *p = (int *)malloc(sizeof(int) * 10);
    for (size_t i = 0; i < 10; i++)
        p[i] = i + 1;
    printf("It is %d\n", sum(p, (p + 10)));
    return 0;
}
