#include <stdio.h>

int main(int argc, char const *argv[])
{
    // int a;
    char fn[128];
    char full_fn[256];
    // ignore chars preceding the integer
    // scanf("%*s %d",&a);
    scanf("%s",&fn);
    sprintf(full_fn,"/root/%s",fn);
    // printf("Input value read : a = %d",a);
    printf("Input full path is : %s",full_fn);
    return 0;
}
