#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <stdint.h>

int main(void)
{
    unsigned int n = UINT_MAX;
    int x = sizeof(int);
    int y = sizeof(3.14);
    int z = sizeof(3.14f);
    int8_t i8 = sizeof(int8_t);
    int_least8_t il8 = sizeof(int_least8_t);
    int_fast8_t if8 = sizeof(int_fast8_t);
    // for (unsigned int i = 100; i >= 0; --i)
    // {
        // printf("Loop sign number %d\n", i);
    // }
    printf("size of int %d\n", x);
    printf("size of 3.14 is %d\n", y);
    printf("size of 3.14F is %d\n", z);
    printf("size of int is %zd\n", sizeof(int));
    printf("size of int8_t is %d\n", i8);
    return 0;   
}