#include <stdio.h>

int a = 4;

int hint(void)
{
    printf("5\n");
    return 0;
}

int main(void)
{
    printf("%d\n", a);
    hint();
    return 0;
}

