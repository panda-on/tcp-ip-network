#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define FILE_NAME_SZ 128
#define FULL_PATH_SIZE 256
#define BUF_SZ 1024

void error_handling(char *message);
int send_file(int sock, char *file_name);

/*
    application description:
        1. the server send file to the client using tcp/ip protocal
        2. the file directory is the where the programme runs
        3. the client send the file name wanted
        4. if the file requested by client exists, the file send server
            send file to the client, disconnect otherwise
    application layer protocal:
        1. the client send file name to the server
        2. the server send file content to the client
        3. the path where runing the server programme is the directory visible for client
    note:
        DO NOT EXECUTE THE CLIENT AND THE SERVER IN THE SAME DIECTORY
*/

int main(int argc, char const *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_sz;
    char fn[BUFFER_SIZE];
    char buf[BUFFER_SIZE];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("failed to set socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("failed to bind");
    if (listen(serv_sock, 5) == -1)
        error_handling("failed to listen");

    clnt_addr_sz = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
    if (clnt_sock < 0)
        error_handling("accept() error");
    else
        printf("Client connected\n");

    recv(clnt_sock, fn, BUFFER_SIZE, 0);
    send_file(clnt_sock, fn);

    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

/*
    input args: socket descriptor, file name
    output args: length of sent content
*/
int send_file(int sock, char *file_name)
{
    int snd_cnt, n;
    FILE *src_fp;
    char wrt_buf[BUFFER_SIZE];

    if ((src_fp = fopen(file_name, "rb")) == NULL)
        error_handling("Failed to open file");

    n = 1;
    snd_cnt = 0;
    while (n > 0)
    {
        bzero(wrt_buf, BUFFER_SIZE);
        n = fread(wrt_buf, 1, BUFFER_SIZE, src_fp);
        if (n < 0)
            error_handling("Failed to read file");

        if (n == 0)
            break;

        snd_cnt = send(sock, wrt_buf, n, 0);
        if (snd_cnt < 0)
            error_handling("Failed to send bytes");
        snd_cnt += n;
    }
    colse(src_fp);
    return snd_cnt;
}