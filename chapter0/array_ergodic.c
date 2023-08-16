#include <stdio.h>

int sum(int* start, int* end)
{
    int total = 0;
    while (start < end)
    {
        total += *start;
        printf("add %d\t", *start);
        start ++;
    }
    printf("\n");
    return total;
}

int main(int argc, char const *argv[])
{
    int arr[6] = {1, 1, 1, 1, 1, 1};
    printf("the sum of arr is %d\n", sum(arr, arr+6));
    return 0;
}
