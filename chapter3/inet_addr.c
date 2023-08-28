#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
void error_handling(char *message);

int main(int argc, char const *argv[])
{
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";

    /* trans dotted decimal notation to integer form ip adddress using inet_addr */
    unsigned long conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE)
    {
        printf("Transforming Error occured!\n");
    }
    else
    {
        printf("Network ordered integer addr: %#lx \n", conv_addr);
    }

    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE)
    {
        printf("Transforming Error occured!\n");
    }
    else
    {
        printf("Network ordered integer addr: %#lx \n\n", conv_addr);
    }

    /* trans dotted decimal natation ip address to integer form using inet_aton*/
    struct sockaddr_in addr_inet;
    if (!inet_aton(addr1, &addr_inet.sin_addr))
        error_handling("Coversion error\n");
    else
        printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);
    
    /* trans IP address at network byte order in integer form to string form */
    struct sockaddr_in addr3, addr4;
    char *str_ptr;
    char str_arr[20];

    addr3.sin_addr.s_addr=htonl(0x01020304);
    addr4.sin_addr.s_addr=htonl(0x1010101);

    str_ptr=inet_ntoa(addr3.sin_addr);
    strcpy(str_arr,str_ptr);
    printf("Dotted-Decimal notation of addr3: %s \n", str_ptr);

    inet_ntoa(addr4.sin_addr);
    printf("Dotted-Decimal notation of addr4: %s \n", str_ptr);
    printf("Dotted-Decimal notation of addr3: %s \n", str_arr);

    return 0;
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
