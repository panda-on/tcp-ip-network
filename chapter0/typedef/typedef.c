#include <stdio.h>

/* typedef used to define a data type to a custome name */
typedef unsigned char BYTE;
typedef int *intptr;
typedef int five_ints[5];

typedef char *string;

typedef char (*Func)(void);
typedef Func Arr[5];
Arr* x(void);

int main(int argc, char const *argv[])
{
    BYTE c = 'z';
    printf("%c\n", c);
    int a = 65;
    intptr x = &a;
    five_ints i5 = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d\t", i5[i]);
    }

    string str = "Hello,World!";
    printf("%s\n", str);

    char (*(*x(void))[5])(void);
    return 0;
}

