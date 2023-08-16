#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i = 10;
    void *p = &i;
    int *q = NULL;
    q = p;
    printf("get pointer q: %d\n", *q);
    return 0;
}
