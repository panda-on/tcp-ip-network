#include <stdio.h>
#include <string.h>

int main()
{
    char *str1 = "Hello";
    char *str2 = "World";
    char str3[strlen(str1)+strlen(str2)];

    // 添加字符串结束符
    strcat(str3, str1);
    strcat(str3, str2);
    printf("%s", str3);

    return 0;
}