#include <stdio.h>
#include <stdlib.h>
#include "../../util.c"
unsigned long Fibonacci(unsigned n);
/* quote external function */
extern int sum_arr(int *start, int len);
void counter(void);

int main(int argc, char const *argv[])
{
    printf("Enter the number of terms in the Fibonacci sequence to calculate: ");
    int n;
    scanf("%d", &n);
    printf("After %d generation there is %zd rabbits\n", n, Fibonacci(n));
    /* function pointer */
    unsigned long (*fb_ptr)(unsigned) = Fibonacci;
    printf("calling Fibonacci function by function pointer: %zd\n", (*fb_ptr)(n));
    printf("calling Fibonacci function by function pointer: %zd\n", fb_ptr(n));

    int arr[5] = {1, 2, 4, 5, 6};
    printf("sum of array is %d\n", sum_arr(arr, 5));

    exit(EXIT_SUCCESS);
    return 0;
}

/* define a function calling itself, const qualifier control parameter can't 
be change inside the function */
unsigned long Fibonacci(const unsigned n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

void counter(void)
{
    /* static qualifier control variable initiate only 1 time, control function 
    can only be used at current file */
    static int count = 1;
    printf("%d\n", count);
    count++;
}