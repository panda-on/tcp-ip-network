#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    unsigned int ui = UINT_MAX;

    if (0.1 + 0.2 == .3)
        printf(".1 + .2 = .3");
    printf(".1 + .2 != .3 in C\n");   
    bool flag = false;
    if (!flag)
    {
        printf("bool loop is entered!\n");
    }
     
    return 0;
}
