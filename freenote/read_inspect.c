#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int fd = open("hello.txt", O_RDONLY);
    char *buf = (char *)malloc(sizeof(char) * 10);
    if (buf == NULL)
    {
        printf("allocate error.\n");
        return 1;
    }

    size_t nbyte = 5;
    ssize_t read_size = read(0, buf, 1);
    if (read_size == -1)
    {
        printf("Read error.\n");
        return 1;
    }
    printf("%s\n", buf);
    printf("read_size: %zu\n", read_size);

    // read_size = read(fd, buf, nbyte);
    // if (read_size == -1)
    // {
    //     printf("Read error.\n");
    //     return 1;
    // }
    // printf("%s\n", buf);
    // printf("read_size: %zu\n", read_size);

    // read_size = read(fd, buf, nbyte);
    // if (read_size == -1)
    // {
    //     printf("Read error.\n");
    //     return 1;
    // }
    // printf("%s\n", buf);
    // printf("read_size: %zu\n", read_size);

    if (close(fd == -1))
    {
        printf("Close error.\n");
        return 1;
    }
    return 0;
}
