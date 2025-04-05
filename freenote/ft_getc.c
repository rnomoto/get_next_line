#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>

int ft_getc(int fd)
{
    static char buf[BUFSIZ]; //read to this valuable
    static int fd_store = -1;
    static ssize_t read_size;
    
    static int i = 0;
    //printf("fd: %d\n", fd);

    if (fd_store == fd)
        i++;
    else
    {
        i = 0;
        read_size = read(fd, buf, sizeof buf); 
        //printf("read_size: %zu\n", read_size);
        if (read_size == -1)
            return EOF;
        else if (read_size == 0)
            return EOF;
        fd_store = fd;
    }
    if (read_size == 0)
        return EOF;
    read_size --;
    return buf[i];
}

int main(void)
{
    int fd;
    int c;

    fd = open("hello.txt", O_RDONLY);
    while (1)
    {
        c = ft_getc(fd);
        if (c == EOF)
            break;
        printf("%c", c);
    }
    close(fd);

    // int fd = open("hello.txt", O_RDONLY);
    // int c = ft_getc(fd);
    // if (c == EOF)
    //     printf("error\n");
    // else
    //     printf("%c\n", c);
    
    // int fd2 = open("number.txt", O_RDONLY);
    // c = ft_getc(fd2);
    // if (c == EOF)
    //     printf("error\n");
    // else
    //     printf("%c\n", c);
    
    // c = ft_getc(fd);
    // if (c == EOF)
    //     printf("error\n");
    // else
    //     printf("%c\n", c);

    // close(fd);
    // close(fd2);

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