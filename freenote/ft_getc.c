#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>

int ft_getc(int fd)
{
    static char buf[BUFSIZ]; //read to this valuable
    static int fd_store;
    ssize_t read_size;
    
    static int i = 0;
    printf("fd: %d\n", fd);

    if (fd_store == fd)
        i++;
    else
    {
        i = 0;
        read_size = read(fd, buf, sizeof buf); 
        printf("read_size: %zu\n", read_size);
        if (read_size == -1)
            return EOF;
        fd_store = fd;
    }
    return buf[i];
}

int main(void)
{
    int fd = open("hello.txt", O_RDONLY);
    int c = ft_getc(fd);
    if (c == EOF)
        printf("error\n");
    else
        printf("%c\n", c);
    
    int fd2 = open("number.txt", O_RDONLY);
    c = ft_getc(fd2);
    if (c == EOF)
        printf("error\n");
    else
        printf("%c\n", c);
    
    c = ft_getc(fd);
    if (c == EOF)
        printf("error\n");
    else
        printf("%c\n", c);

    close(fd);
    close(fd2);

    // FILE *fp = fopen("hello.txt", "r");
    // int c = getc(fp);
    // if (c == EOF)
    //     printf("error\n");
    // else
    //     printf("%c\n", c);
    
    // FILE *fp2 = fopen("number.txt", "r");
    // c = getc(fp2);
    // if (c == EOF)
    //     printf("error\n");
    // else
    //     printf("%c\n", c);
    
    // c = getc(fp);
    // if (c == EOF)
    //     printf("error\n");
    // else
    //     printf("%c\n", c);

    // fclose(fp);
    // fclose(fp2);

    return 0;
}