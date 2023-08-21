#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* define struct data type  */
struct car
{
    char *name;
    float price;
    int speed;
};

struct book
{
    float price;
    char *title;
    char *author;
    char *publisher;
};

struct name
{
    char fisrt_name[50];
    char last_name[50];
};

struct student
{
    struct name name;
    short age;
    char sex;
};

/* struct self reference to itself */
struct node
{
    int data;
    // next containes the address of the next struct node
    struct node *next;
};

/* define flexible array, the flexible member has to be the
 last member of the struct */
struct vstring
{
    int len;
    char chars[];
};

void rename_book(struct book *bk, char *new_book_name)
{
    /* the operation . is prior to operation *, so use parenthesis to higher the
    priority of operation * . As for struct pointer, use -> operation to get the
    property of a struct */
    bk->title = new_book_name;
};

int main(int argc, char const *argv[])
{

    struct car saturn = {"Saturn SL/2", 160000.98, 200};
    saturn.speed = 210;

    struct book financial_thinking = {
        .title = "Finacial Thinking",
        .author = "Lichengcai",
        .price = 69.0,
        .publisher = "中信教育出版社"};

    /* struct pointer */
    struct book *b1 = &financial_thinking;
    printf("The price of financial thinking is %f\n", b1->price);

    /* struct array */
    struct book books[10];
    books[0].title = "book-name1";
    books[0].author = "author1";
    books[0].price = 13.98;
    books[0].publisher = "中信出版社";

    /* struct takes not only just the sum of all its properties byte width,
    but the largest byte width times the struct's property number, it's designed to
    accelerate the speed of reading and writing */
    printf("The byte size of financial_thinking is %zd\n", sizeof(struct book));

    /* the different order of property in struct will not affect the byte size
    of the struct with gcc at version 11.4.0 */
    struct foo
    {
        char c;
        int a;
        char *b;
    };

    printf("The byte size of struct foo is %zd\n", sizeof(struct foo));

    struct bar
    {
        char *b;
        int a;
        char c;
    };

    printf("The byte size of struct bar is %zd\n", sizeof(struct bar));

    /* copy struct */
    books[0] = financial_thinking;
    printf("The name of books[0] is %s\n", books[0].title);

    /* operate struct property */
    rename_book(&books[0], "Principal");
    printf("The name of books[0] is %s\n", books[0].title);

    /* nested struct data type */
    struct student sdt1;
    struct student sdt2;
    strcpy(sdt1.name.fisrt_name, "Harry");
    strcpy(sdt1.name.last_name, "Potter");

    printf("This student names %s %s\n", sdt1.name.fisrt_name, sdt1.name.last_name);

    /* node referenct to itself */
    struct node *head;

    head = malloc(sizeof(struct node));

    head->data = 11;
    head->next = malloc(sizeof(struct node));

    head->next->data = 22;
    head->next->next = malloc(sizeof(struct node));

    head->next->next->data = 33;
    head->next->next->next = NULL;

    struct node *curr_ptr = head;

    while (curr_ptr != NULL)
    {
        printf("node data is %d\n", head->data);
        curr_ptr = curr_ptr->next;
    }

    for (struct node *cur = head; cur != NULL; cur = cur->next)
    {
        printf("%d\n", cur->data);
    }

    /* bit field */
    struct bit_field
    {
        unsigned int ab : 1;
        unsigned int cd : 1;
        unsigned int ef : 1;
        unsigned int gh : 1;
    };
    printf("The size of bit_fields is %zd\n", sizeof(struct bit_field));

    /* flexible array member */
    int char_len = 100;
    struct vstring *str = malloc(sizeof(struct vstring) + char_len * sizeof(char));
    str->len = char_len;
    for (size_t i = 0; i < str->len; i++)
    {
        str->chars[i] = 65 + i;
    }
    printf("The member chars of vstring is %s\n", str->chars);

    return 0;
}
