#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 1024
#define OP_SZ 4
#define RSLT_SZ 4
#define TMP_SZ 4
void error_handling(char *message);

/*
    1. 按照约定的协议向服务端发送操作数和操作符号
    2. 将计算结果打印到控制台
*/
int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    socklen_t serv_addr_sz;
    unsigned int operand_cnt;
    char msg[BUF_SIZE];
    int op_cnt;
    int idx;
    int result;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("failed to set socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr_sz = sizeof(serv_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, serv_addr_sz) == -1)
        error_handling("failed to connect server");
    else
        printf("Connected! \n");

    fputs("Input Operand Count: \n", stdout);
    scanf("%d", &operand_cnt);
    msg[0] = (char)operand_cnt;
    for (idx = 0; idx < operand_cnt; idx++)
    {
        char *tmp[TMP_SZ];
        int temp;
        printf("Input Operand %d\n", idx + 1);
        scanf("%d", (int *)&msg[idx * OP_SZ + 1]);
    }
    fgetc(stdin);
    fputs("Input Operator: \n", stdout);
    scanf("%c", &msg[OP_SZ * operand_cnt + 1]);
    write(sock, msg, OP_SZ * operand_cnt + 2);
    read(sock, &result, RSLT_SZ);
    printf("Operation result : %d\n", result);
    close(sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
