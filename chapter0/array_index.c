#include <stdio.h>

int main(int argc, char const *argv[])
{
    int arr[100];
    
    for (size_t i = 0; i < 100; i++)
    {
        printf("list[%zd] is %d\n", i, arr[99]);
    }

    // use sizeof operation to get the length of array
    printf("size of arr is %zd", sizeof(arr)/sizeof(arr[99]));
    
    return 0;
}
