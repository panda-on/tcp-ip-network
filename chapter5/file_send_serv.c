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
int send_file(int sock, char *path_to_file);

/*
    application description: the server send file to the client using tcp/ip protocal
    the file directory is /root
    the client request the sepecified file name
    if the file requested by client exists, the file send server send file to the client,
    disconnect otherwise
    application layer protocal
    the first byte is contains the length of the file name
    length of file name is less than 128 bytes
*/

int main(int argc, char const *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_sz;
    char *path = "/root";
    // FILE *file;
    unsigned int fn_len;
    char fn[FULL_PATH_SIZE];
    int read_cnt;
    // struct hostent server;
    // gethostbyname(argv[1])

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
    for (size_t i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
        if (clnt_sock < 0)
            error_handling("accept() error");
        else
            printf("Connected client %zd \n", i + 1);

        recv(clnt_sock, fn, FULL_PATH_SIZE, 0);

        send_file(clnt_sock, fn);

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

/*
    input args: socket descriptor, file path, file name
    output args: length of sent content
*/
int send_file(int sock, char *path_to_file)
{
    int snd_cnt, read_cnt, n;
    FILE * src_fp;
    char wrt_buf[BUFFER_SIZE];
    char buf[BUFFER_SIZE];

    if ((src_fp = fopen(path_to_file, "w")) == NULL)
        error_handling("Failed to open file");

    n = 1;
    while (n > 0)
    {
        bzero(buf, BUFFER_SIZE);
        n = fread(buf, BUFFER_SIZE - 1, 1, src_fp);
        if (n < 0)
            error_handling("Failed to read file");

        if (n == 0)
            break;

        snd_cnt = send(sock, buf, BUFFER_SIZE, 0);
        if (snd_cnt < 0)
            error_handling("Failed to send bytes");
    }
}