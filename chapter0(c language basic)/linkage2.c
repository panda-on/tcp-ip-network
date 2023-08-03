#include <stdio.h>
// add linkage of source file linkage1.c
#include "linkage1.c"

int main()
{
    call_me();
    printf("\n having fun washing!");
    animals = 10;
    printf("%d\n", animals);
    return 0;
}
