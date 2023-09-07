#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF_SIZE 1024
void error_handling(char *message);

/*
    1. 客户端接收用户输入的字符并发送到服务端
    2. 服务端和客户端之间的字符串回声一直执行到客户端输入Q为止
    3. 服务端在同一时刻只与一个客户端相连
    4. 服务端依次向5个客户端提供服务并退出
    5. 服务端将接收的字符串数据回传客户端
*/

int main(int argc, char const *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_addr_sz;

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    clnt_addr_sz = sizeof(serv_addr);

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    /* 迭代处理5个客户端的请求，结束后关闭服务端套接字 */
    for (size_t i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
        if (clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("Connected client %zd \n", i + 1);

        while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
            write(clnt_sock, message, str_len);

        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}

/*
    问题：
        1. 错误的假设：每次read和write会以字符串为单位执行实际I/O操作
*/