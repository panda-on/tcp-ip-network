#include <stdio.h>

int main(int argc, char const *argv[])
{
    int op_cnt, i;
    char msg[100];
    fputs("Input Operand Count: \n", stdout);
    // scanf("%d", (int *)&msg[0]);
    scanf("%d", &op_cnt);
    msg[0] = (char)op_cnt;
    for (int i = 0; i < op_cnt; i++)
    {
        printf("Input a number: \n");
        scanf("%d", (int *)&msg[i * 4 + 1]);
    }

    for (size_t i = 0; i < op_cnt; i++)
    {
        printf("msg 0 is %d \n", *(int *)(msg + 4*i +1));
    }

    return 0;
}
