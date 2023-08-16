#include <stdio.h>

static int animals = 8;
const int i = 5;

int call_me(void)
{
    printf("%d %d\n", i, animals);
    return 0;
}


