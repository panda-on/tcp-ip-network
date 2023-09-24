#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

void error_handling(char *message);

int main(int argc, char const *argv[])
{

    int tcp_sock, udp_sock;
    int sock_type;
    socklen_t optlen;
    int state;
    // socket type define
    printf("Socket Type Definition\n");
    printf("SOCK_STREAM: %d\n", SOCK_STREAM);
    printf("SOCK_DGRAM: %d\n", SOCK_DGRAM);

    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);

    // get sock type option value and print to console
    state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
    if(state)
        error_handling("getsockopt() error");
    printf("Socket type 1 : %d \n",sock_type);

    state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
    if(state)
        error_handling("getsockopt() error");
    printf("Socket type 2: %d \n",sock_type);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}