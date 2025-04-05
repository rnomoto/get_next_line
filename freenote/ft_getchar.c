#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int ft_getchar(void)
{
    static char buf[BUFSIZ]; //read to this valuable
    static int first_read = 0;
    ssize_t read_size;
    
    static int i = 0;

    if (first_read == 0)
    {
        read_size = read(0, buf, sizeof buf); 
        //read the whole line at first
        if (read_size == -1)
            return EOF;
        else if (read_size == 0)
            return EOF;
        i++;
    }
    else if (buf[i] == '\0')
        return EOF;
    else
    {
        i++;
        if (buf[i] == '\0')
            return EOF;
    }
    first_read++;
    return buf[i];
}

int main(void)
{
    int c = ft_getchar();
    if (c == EOF)
        printf("error\n");
    else
        printf("%c\n", c);
    c = ft_getchar();
    if (c == EOF)
        printf("error\n");
    else
        printf("%c\n", c);
    c = ft_getchar();
    if (c == EOF)
        printf("error\n");
    else
        printf("%c\n", c);

    // int c = getchar();
    // printf("%c\n", c);
    // c = getchar();
    // printf("%c\n", c);
    // c = getchar();
    // printf("%c\n", c);

    return 0;
}
