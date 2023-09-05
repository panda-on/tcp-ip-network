#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SZ 1024
#define OP_SZ 4
#define RSLT_SZ 4
void error_handling(char *message);

/*
    应用层协议设计：
    1. 通过tcp获取客户端的操作数和操作符
    2. 将操作数和操作符进行操作，操作完后返回计算结果
*/
int main(int argc, char const *argv[])
{
    int clnt_sock, serv_sock;
    struct sockaddr_in clnt_addr, serv_addr;
    socklen_t clnt_addr_sz;
    char message[BUF_SZ];
    int op_cnt;
    int result;
    char operator;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("failed to set socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("failed to bind");
    if (listen(serv_sock, 5) == -1)
        error_handling("failed to listen");

    clnt_addr_sz = sizeof(clnt_addr);
    int read_len;
    for (size_t i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
        if (clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("Connected client %zd \n", i + 1);

        while ((read_len = read(clnt_sock, message, BUF_SZ)) != 0)
            write(clnt_sock, message, read_len);

        op_cnt = (int)message[0];
        operator= message[op_cnt * OP_SZ + 1];
        if (!strcmp("+", &operator))
        {
            for (size_t i = 0; i < op_cnt; i++)
            {
                result += *(int *)&message[i * OP_SZ + 1];
            }
        }

        if (!strcmp("-", &operator))
        {
            for (size_t i = 0; i < op_cnt; i++)
            {
                result -= *(int *)&message[i * OP_SZ + 1];
            }
        }

        if (!strcmp("*", &operator))
        {
            for (size_t i = 0; i < op_cnt; i++)
            {
                result *= *(int *)&message[i * OP_SZ + 1];
            }
        }
        write(clnt_sock, &result, RSLT_SZ);
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}