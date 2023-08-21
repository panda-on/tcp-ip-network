#include <stdio.h>
#include <stdlib.h>
#include "../../util.c"
#include <string.h>

/* define a function to copy memory */
void *my_memcpy(void *dest, void *src, int byte_count);

int main(int argc, char const *argv[])
{
    // allocate a block of memory used to store an array with 10 elements
    int *p = (int *)malloc(sizeof(int) * 10);
    for (size_t i = 0; i < 10; i++)
        p[i] = i + 1;
    printf("The sum of array is %d\n", sum_arr(p, 10));

    // initiate memory allocated from function malloc()
    char *p1 = malloc(13);
    if (p1 == NULL)
    {
        puts("Error to malloc memory");
    }
    strcpy(p1, "Hello,world!");
    printf("%s\n", p1);

    // use free() to free memory allocated from malloc()
    free((void *)p1);

    // use calloc() to allocate memory
    char *p2 = calloc(13, 1);
    int *int_arr = calloc(5, sizeof(int));
    strncpy(p2, "Hello,World!", 12);
    strncpy(p2 + 12, "\0", 1);
    for (size_t i = 0; i < 5; i++)
    {
        int_arr[i] = (int)i;
        printf("%d\n", int_arr[i]);
    }
    free(p2);
    free(int_arr);

    printf("----- realloc() ------\n");
    // use realloc() to adjust the allocated memory block
    int *b = NULL;
    b = malloc(sizeof(int) * 10);
    b = realloc(b, sizeof(int) * 200);
    if (b == NULL)
    {
        printf("Error reallocing\n");
    }
    free(b);

    /* use restrict modifier to control the accessing of
    memory block */
    int *restrict p3 = malloc(sizeof(int) * 10);
    int *restrict p3c = malloc(sizeof(int) * 10);

    /* use memcpy() to copy memory from one place to another */
    printf("----- memcpy() ------\n");
    for (size_t i = 0; i < 10; i++)
    {
        p3[i] = i;
    }
    memcpy(p3c, p3, sizeof(int) * 10);
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d\n", p3c[i]);
    }

    char *s = "hello,world";
    size_t len = strlen(s) + 1;
    char *c = malloc(len);

    if (c)
    {
        memcpy(c, s, len);
    }
    printf("%s\n", c);
    my_memcpy(c, "Hello,World", len);
    printf("%s\n", c);
    free(c);

    printf("----- memmove() ------\n");
    char x[] = "Home Sweet Home";
    printf("%s\n", (char *)memmove(x, &x[5], 10));

    printf("----- memcmp() ------\n");
    printf("%d\n", memcmp("A", "C", 1));

    return 0;
}

void *my_memcpy(void *dest, void *src, int byte_count)
{
    char *d = dest;
    char *s = src;
    while (byte_count--)
    {
        *d++ = *s++;
    }
    return dest;
}