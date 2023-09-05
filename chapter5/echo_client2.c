#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    int str_len, str_cnt, recv_len;

    if (argc != 3)
    {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("failed to create a socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("failed to connect");
    else
        puts("Connected......");

    while (1)
    {
        fputs("Input a message (Q to quit)\n", stdout);
        fgets(message, BUF_SIZE, stdin);

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        str_len = strlen(message);
        write(sock, message, strlen(message));

        /* 考虑数据太长，可能服务端一个数据包发不过来的情况 */
        recv_len = 0;
        str_cnt = 0;
        while (str_len > str_cnt)
        {
            str_cnt = read(sock, message, BUF_SIZE - 1);
            recv_len += str_cnt;
        }
        message[str_len] = 0;
        printf("Message from server : %s", message);
    }
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}