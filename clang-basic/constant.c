#include <stdio.h>

const int c_var = 20;
const int* ptr = &c_var;
// const int* const ptr = &c_var;
char string [] = "this is a string in C";
int main()
{
    printf("%d \n", c_var);
    printf("%d \n", *ptr);
    printf("%s \n", string);
    return 0;
}