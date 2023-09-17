#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char *msg);
void start_service(const char *ip_addr, const char *port_str);

int main(int argc, char const *argv[])
{

    if (argc != 3)
    {
        printf("Usage : %s <host> <port>\n", argv[0]);
        exit(1);
    }

    start_service(argv[1], argv[2]);
    return 0;
}

void start_service(const char *ip_addr, const char *port_str)
{
    int sock, msg_len;
    struct sockaddr_in you_addr;
    char msg[BUF_SIZE];
    char msg1[] = "Hi";
    char msg2[] = "I'm another UDP host!";
    char msg3[] = "Nice to meet you";
    socklen_t you_addr_sz;

    memset(&you_addr, 0, sizeof(you_addr));
    you_addr.sin_family = AF_INET;
    you_addr.sin_addr.s_addr = inet_addr(ip_addr);
    you_addr.sin_port = htons(atoi(port_str));

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        error_handling("UDP socket creation error!");

    sendto(sock, msg1, strlen(msg1), 0, (struct sockaddr *)&you_addr, sizeof(you_addr));
    sendto(sock, msg2, strlen(msg2), 0, (struct sockaddr *)&you_addr, sizeof(you_addr));
    sendto(sock, msg3, strlen(msg3), 0, (struct sockaddr *)&you_addr, sizeof(you_addr));

    close(sock);
}

void error_handling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}