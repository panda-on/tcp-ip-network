#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUF_SIZE 30

void error_handling(char *message);
void start_echo_service(uint16_t portno);

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    start_echo_service(htons(atoi(argv[1])));

    return 0;
}

void start_echo_service(uint16_t portno)
{
    int sock, str_len;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_sz;
    char message[BUF_SIZE];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
        error_handling("UDP socket creation error!");
    else
        printf("create UDP socket successed!\n");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = portno;

    if (bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("UDP socket bind address error!");

    while (1)
    {
        clnt_addr_sz = sizeof(clnt_addr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
        printf("Message from client: %s",message);
        sendto(sock, message, str_len, 0, (struct sockaddr *)&clnt_addr, clnt_addr_sz);
    }

    close(sock);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}