#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char *server_port = "9190";
    htonl(INADDR_ANY);
    printf("%#x", htons(atoi(server_port)));
    return 0;
}
