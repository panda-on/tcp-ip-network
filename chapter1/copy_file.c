#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF_SIZE 1024

int main(int argc, char const *argv[])
{
    if (argc != 3)
        printf("Usage: src_file_name dest_file_name\n");

    char buf[BUF_SIZE];
    int src_fd, dest_fd;

    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1)
    {
        printf("open() error!\n");
    }

    dest_fd = open(argv[2], O_CREAT | O_WRONLY);
    if (dest_fd == -1)
    {
        printf("open() error!\n");
    }

    /* every time call read function, the it will remember the reading offest of this time of reading
    ,the next time you read the file again, it won't read start at the begin but the offset of the 
    last time read */
    int readBytes;
    while ((readBytes = read(src_fd, buf, BUF_SIZE)) > 0)
    {
        write(dest_fd, buf, readBytes);
    }

    close(dest_fd);
    close(src_fd);

    return 0;
}
