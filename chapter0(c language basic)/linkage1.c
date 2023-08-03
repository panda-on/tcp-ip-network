#include <stdio.h>
// add linkage of source file linkage0.c
#include "linkage0.c"

int main(void)
{
    call_me();
    animals = 2;
    printf("%d\n", animals);
}

