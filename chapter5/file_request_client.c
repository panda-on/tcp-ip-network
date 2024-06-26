#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define FULL_PATH_SIZE 256

void error_handling(char *message);
// int recv_file(int sock, char *full_fn);

/*
    application protocal:
        first byte send the length of filename
        the following bytes is made of file name
    steps:
        #0: read a file name from terminal
        #1: send file name
        #2: read file content from server
        #3: close file
        #4: close socket
*/
int main(int argc, char const *argv[])
{
    int sock, n, bytes_recv;
    FILE *fd;
    struct sockaddr_in serv_addr;
    socklen_t serv_addr_sz;
    char fn[BUFFER_SIZE];
    char buf[BUFFER_SIZE];

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

    fputs("Input file name which you want to get from the server: \n", stdout);
    scanf("%s", fn);
    write(sock, fn, strlen(fn));

    bytes_recv = 0;
    n = 1;
    fd = fopen(fn, "wb");
    while (n > 0)
    {
        bzero(buf, BUFFER_SIZE);
        n = recv(sock, buf, BUFFER_SIZE, 0);
        if (n < 0)
            error_handling("Could not fetch file\n");
        if (n == 0)
            break;
        fwrite(buf, n, 1, fd);
    }
    printf("Received file: %s\n", fn);
    fclose(fd);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

/*
    create file received from server
*/
// int recv_file(int sock, char *full_fn)
// {
//     int fd;
//     char read_buf[BUFFER_SIZE];
//     int read_cnt;
//     int write_cnt;

//     fd = open(full_fn, O_WRONLY | O_RDONLY | O_CREAT);

//     while ((read_cnt = read(sock, read_buf, BUFFER_SIZE - 1)) != 0)
//     {
//         write(fd, read_buf, read_cnt);
//         write_cnt += read_cnt;
//     }

//     close(fd);
//     return write_cnt;
// }
