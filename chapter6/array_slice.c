#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char str[] = "where my heart settle, where is my home";
    char result[10];
    strncpy(result,str,10);
    // sprintf(result,"%.*s",10,str);
    // printf("the first 10 character is: %s",result);
    printf("the first 10 character is %s",str[0,9]);
    return 0;
}
