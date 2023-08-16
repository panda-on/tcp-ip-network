#include <stdio.h>

int sum_arr(int *start, int len)
{
    int total = 0;
    for (size_t i = 0; i < len; i++)
        total += *(start + i);
    return total;
}