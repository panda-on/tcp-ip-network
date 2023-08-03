#include <stdio.h>
#include "linkage0.c"

int main(void)
{
    call_me();
    animals = 2;
    printf("%d\n", animals);
}

