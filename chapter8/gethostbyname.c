#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

void error_handling(char *message);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <hostname> \n", argv[0]);
        exit(1);
    }

    struct hostent *host_info;
    host_info = gethostbyname(argv[1]);
    if(!host_info)
        error_handling("get host error!");
    // Official Hostname
    printf("Official Hostname : %s \n",host_info->h_name);
    // Host Aliases
    for (int i = 0; host_info->h_aliases[i]; i++)
    {
        printf("Host Alias %d : %s\n", i + 1, host_info->h_aliases[i]);
    }
    // Address Type
    printf("Address Type %s\n", (host_info->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
    // IP Addresses
    for (int i = 0; host_info->h_addr_list[i]; i++)
    {
        printf("IP Address %d : %s\n", i+1, inet_ntoa(*(struct in_addr*)host_info->h_addr_list[i]));
    }
    
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}