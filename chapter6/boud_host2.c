#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char *msg);

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    start_service(argv[1]);
    return 0;
}

void start_service(char *port_str)
{
    int sock, msg_len;
    struct sockaddr_in my_addr, you_addr;
    char msg[BUF_SIZE];
    char msg1[] = "Hi";
    char msg2[] = "I'm another UDP host!";
    socklen_t you_addr_sz;

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
    my_addr.sin_port = htons(atoi(port_str));

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        error_handling("UDP socket creation error!");

    if (bind(sock, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
        error_handling("failed to bind UDP socket with address");

    for (size_t i = 0; i < 3; i++)
    {
        sleep(3);
        you_addr_sz = sizeof(you_addr);

        printf("Message %d : %s \n", i + 1, msg);
    }
    close(sock);
}

void error_handling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}