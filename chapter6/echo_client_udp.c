#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char *message);
void start_echo_client(in_addr_t ip, uint16_t portno);

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Usage : %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    start_echo_client(inet_addr(argv[1]), htons(atoi(argv[2])));
    return 0;
}

void start_echo_client(in_addr_t ip, uint16_t portno)
{
    int sock, str_len;
    struct sockaddr_in serv_addr, from_addr;
    socklen_t adr_sz;
    char message[BUF_SIZE];
    

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        error_handling("UDP socket creation error!");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = ip;
    serv_addr.sin_port = portno;

    while (1)
    {
        fputs("Input message(q to quit): ", stdout);
        fgets(message, sizeof(message), stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        sendto(sock, message, strlen(message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        adr_sz = sizeof(from_addr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr *)&from_addr, &adr_sz);
        message[str_len] = 0;
        printf("Message from server: %s", message);
    }
    close(sock);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}