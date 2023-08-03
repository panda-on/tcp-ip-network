#include <stdio.h>
#define pi 3.14


int main(void)
{
    // defining an integer constant
    const int var = 10;
    printf("The value of constant var is %d\n",var);
    // defining a pointer to that const variable
    // int* ptr = &var;
    // changing value
    // *ptr = 500;
    printf("The value of constant var is %d\n",var);
    printf("My mobile number is "
    " 7\a8\a9\a1\a2\a3\n");
    printf("The value of pi: %.2f\n", pi);
    return 0;
}