#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>

int ft_getc(int fd)
{
    static char buf; //read to this valuable
    static int fd_store = -2; //initialized to a number which is not returned by open()
    static ssize_t read_size;
    
    static int i = 0;

    if (fd_store == fd)
        i++;
    else
    {
        i = 0;
        printf("kkk");
        read_size = read(fd, &buf, 1); 
        if (read_size == -1)
            return EOF;
        else if (read_size == 0)
            return EOF;
        fd_store = fd;
    }
    if (read_size == 0)
        return EOF;
    read_size --;
    return buf;
}

int main(void)
{
    int fd;
    int c;

    fd = open("hello.txt", O_RDONLY);
    c = ft_getc(fd);
    if (c == EOF)
    {
        printf("error\n");
        return 1;
    }
    printf("%c", c);
    close(fd);

    return 0;
}