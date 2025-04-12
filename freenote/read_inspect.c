#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int fd = open("hello.txt", O_RDONLY);

    char *read_buf = (char *)calloc(sizeof(char), 6);
    ssize_t read_size = read(fd, read_buf, 5);
    printf("read_size: %zd\n", read_size);
    printf("read_buf: %s\n", read_buf);
    read_size = read(fd, read_buf, 5);
    printf("read_size: %zd\n", read_size);
    printf("read_buf: %s\n", read_buf);
    read_size = read(fd, read_buf, 5);
    printf("read_size: %zd\n", read_size);
    printf("read_buf: %s\n", read_buf);

    close(fd);
    return 0;
}
