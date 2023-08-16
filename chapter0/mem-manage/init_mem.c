#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // at least allocate 5 bytes to char* to store string abcd, 
    // because the  invisible end sign taking a byte in width will also be write into memory
    char * p = malloc(5);
    strcpy(p, "abcd");
    printf("%s", p);
    return 0;
}
