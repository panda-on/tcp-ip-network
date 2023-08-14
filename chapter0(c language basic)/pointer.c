#include <stdio.h>
#include <stddef.h>

void increament(int* p){
    // 不复制变量的值，直接根据地址修改指定的变量
    // 对于需要大量存储空间的大型变量，指针更加高效
    *p = *p + 1;
}

void increament_2(int p){
    p += 1;
}

int main(int argc, char const *argv[])
{
    int* intPtr = NULL;
    int** foo = NULL;
    short* j1 = NULL;
    short* j2 = NULL;
    int i = 7;
    // increament(&i);
    increament_2(i);
    printf("i is %d\n", i);
    printf("The address of i is %d\n", i);
    j1 = (short*)0x1234;
    j2 = (short*)0x1236;

    ptrdiff_t dist = j2 - j1;
    printf("The distance of two pointer is %td\n", dist);
    return 0;
}
