#include <stdio.h>

// different definition way of function prototype
int sum(int arr[], int len)
{
    int res = 0;
    for (size_t i = 0; i < len; i++)
    {
        res += arr[i];
    }
    return res;
}


int sum2(int* arr, int len)
{
    int res = 0;
    for (size_t i = 0; i < len; i++)
    {
        res += *(arr + i);
    }
    return res;
}


int main(int argc, char const *argv[])
{
    // use get address operator to get the address of the first element 
    // of the array
    int arr[5] = {1, 2, 3, 4, 5};
    int* p = &arr[0];
    
    // in C language, array name is stand for the address of the first 
    // element in the array, so the get address operation can be written
    // in the following way.
    int arr2[5] = {2, 3, 4, 5, 6};
    int* p2 = arr2;
    
    for (size_t i = 0; i < 5; i++)
    {
        printf("arr[%zd] is %d\n", i, *(p+i));
        /* code */
    }
    
    for (size_t i = 0; i < 5; i++)
    {
        printf("arr2[%zd] is %d\n", i, *(p+i));
    }

    printf("The sum of arr is %d\n", sum(arr,sizeof(arr)/sizeof(arr[0])));
    printf("The sum of arr is %d\n", sum2(arr,sizeof(arr)/sizeof(arr[0])));

    return 0;

}
