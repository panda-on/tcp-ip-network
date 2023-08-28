#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    unsigned short host_port=0x1234;
    unsigned short net_port;
    unsigned long host_addr=0x12345678;
    unsigned long net_addr;
    /* trans host byte order to network byte order*/
    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host ordered port: %#x\n",host_port);
    printf("Network ordered port: %#x\n",net_port);
    printf("Host ordered address: %#lx\n",host_addr);
    printf("Network ordered port: %#lx\n",net_addr);

    return 0;
}