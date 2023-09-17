#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MSG_BUF_SIZE 400
void error_handling(char *message);
void start_chat_client(char *ip_str, char *serv_port_str);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage : %s <serv_ip> <serv_port>\n", argv[0]);
        exit(1);
    }
    start_chat_client(argv[1], argv[2]);
    return 0;
}

void start_chat_client(char *ip_str, char *serv_port_str)
{
    int sock, recv_msg_len;
    struct sockaddr_in serv_addr, from_addr;
    socklen_t from_addr_sz;
    char message[MSG_BUF_SIZE];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
        error_handling("UDP socket creation error!");
    else
        printf("create UDP socket successed!\n");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip_str);
    serv_addr.sin_port = htons(atoi(serv_port_str));

    // memset(&my_addr, 0, sizeof(my_addr));
    // my_addr.sin_family = AF_INET;
    // my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // my_addr.sin_port = htons(atoi(clnt_port_str));

    from_addr_sz = sizeof(from_addr);
    while (1)
    {
        fputs("Input a message, press enter to send(q to quit): ", stdout);
        fgets(message,MSG_BUF_SIZE,stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        // scanf("%s", message);
        sendto(sock, message, strlen(message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        recvfrom(sock, message, MSG_BUF_SIZE-1, 0, (struct sockaddr *)&from_addr, &from_addr_sz);
        printf("Message from server: %s\n", message);
    }
    close(sock);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}