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
    if (argc != 2)
    {
        printf("Usage: %s <port>", argv[0]);
        exit(1);
    }

    int serv_sd, clnt_sd, read_cnt;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_sz;
    FILE *fp;
    char buf[BUF_SIZE];

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    serv_sd = socket(AF_INET, SOCK_STREAM, 0);
    if ((bind(serv_sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
        error_handling("failed to create socket");

    listen(serv_sd, 5);

    clnt_addr_sz = sizeof(clnt_addr);
    clnt_sd = accept(serv_sd, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);

    fp = fopen("file_server.c","rb");

    while (1)
    {
        read_cnt = fread((void *)buf, 1, BUF_SIZE, fp);
        if (read_cnt < BUF_SIZE)
        {
            write(clnt_sd, buf, read_cnt);
            break;
        }
        write(clnt_sd, buf, read_cnt);
    }

    fclose(fp);
    // half close socket
    shutdown(clnt_sd, SHUT_WR);
    // show add exception handle
    memset(buf,0,BUF_SIZE);
    read_cnt=read(clnt_sd, buf, BUF_SIZE);
    printf("Message from client: %s\n", buf);
    close(clnt_sd);
    close(serv_sd);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
