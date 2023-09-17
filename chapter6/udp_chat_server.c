#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MSG_BUF_SIZE 400
void error_handling(char *message);
void start_chat_server(char *port_str);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    start_chat_server(argv[1]);
    return 0;
}

void start_chat_server(char *port_str)
{
    int sock, recv_msg_len;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_sz;
    char message[MSG_BUF_SIZE];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0)
        error_handling("UDP socket creation error!");
    else
        printf("create UDP socket successed!\n");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(port_str));

    if (bind(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("UDP socket bind address error!");

    while (1)
    {
        clnt_addr_sz = sizeof(clnt_addr);
        recv_msg_len = recvfrom(sock, message, MSG_BUF_SIZE - 1, 0, (struct sockaddr *)&clnt_addr, &clnt_addr_sz);
        printf("Message from client: %s", message);
        fputs("\nInput a message, press enter to send(q to quit): ", stdout);
        // scanf("%s", message);
        fgets(message, MSG_BUF_SIZE, stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        if (strlen(message) > MSG_BUF_SIZE)
        {
            printf("Message length beyond limit!");
            continue;
        }
        sendto(sock, message, strlen(message), 0, (struct sockaddr *)&clnt_addr, clnt_addr_sz);
    }

    close(sock);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}