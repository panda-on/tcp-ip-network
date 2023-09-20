#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <ip> <port>", argv[0]);
        exit(1);
    }

    int sock, read_cnt;
    struct sockaddr_in serv_addr;
    socklen_t clnt_addr_sz;
    FILE *fp;
    char buf[BUF_SIZE];
    char *return_msg = "Thank you";

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if ((connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
        error_handling("failed to connect server");

    fp = fopen("file_from_server.dat", "wb");

    while (1)
    {
        read_cnt = read(sock, buf, BUF_SIZE - 1);
        if (read_cnt == 0)
            break;
        fwrite((void *)buf, 1, read_cnt, fp);
    }

    printf("File received from server stored in 'file_from_server.dat'");

    write(sock, return_msg, strlen(return_msg));
    fclose(fp);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
