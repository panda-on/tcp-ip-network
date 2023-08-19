#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char str[] = "hello, world!";
    char *str2 = "hello, world!";

    printf("\n%s\n", "--------- string raw value -------------");
    printf("string allocated to str is %s\n", str);
    printf("string allocated to str2 is %s\n", str2);

    printf("\n%s\n", "--------- string value operation -------------");
    printf("string copied to str is %s\n", strcpy(str, "Hello, World!"));
    // printf("string copied to str2c is %s\n", strcpy(str2, "Hello, World!"));

    printf("\n%s\n", "--------- string length operation -------------");
    printf("%s%zd\n", "the length of str is ", strlen(str));
    printf("%s%zd\n", "the length of str2 is ", strlen(str2));
    printf("%s%zd\n", "the size of str is ", sizeof(str));

    printf("\n%s\n", "--------- string copy -------------");
    char *ps = strcpy(str, "Hello,World!");
    puts(ps);
    puts(str2);

    printf("\n%s\n", "---------- string compare ----------");
    int cmp = strcmp("Happy New Year", "Happy Holidays");
    printf("%d\n", cmp);
    int ncmp = strncmp("Happy New Year", "Happy Holidays", 6);
    printf("%d\n", ncmp);

    printf("\n%s\n", "---------- string format ----------");
    char first[6] = "hello";
    char last[6] = "world";
    char s[40];
    sprintf(s, "%s %s", first, last);
    char *str3 = "Wlastlastlastlastlastlastlastlastlastorld World";
    // printf("%d", sprintf(s, "%s %s", first, str3));// 导致溢出
    printf("%d", snprintf(s, 2, "%s %s", first, str3));
    puts(s);

    printf("\n%s\n", "---------- string array ----------");
    char *weekdays[] = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"};

    for (size_t i = 0; i < 7; i++)
    {
        printf("%s\n", weekdays[i]);
    }
    
    return 0;
}
