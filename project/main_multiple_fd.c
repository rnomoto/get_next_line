#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>


//ccw -D BUFFER_SIZE=1
//ccw -D BUFFER_SIZE=10
//ccw -D BUFFER_SIZE=9999
//ccw -D BUFFER_SIZE=1000000
//ccw -D BUFFER_SIZE=0
//ccw -D BUFFER_SIZE=-1
//ccw -D BUFFER_SIZE=999999999

//single_char.txt
//single_line.txt
//multiple_line.txt
//empty.txt
//single_nl.txt
//multiple_nl.txt
//long_line.txt
//long_multiple_line.txt

int main(void)
{
    int fd1 = open("hello.txt", O_RDONLY);
    int fd2 = open("multiple_line.txt", O_RDONLY);
    int fd3 = open("long_multiple_line.txt", O_RDONLY);

    char *line = get_next_line(fd1);
    printf("%s", line);
    free (line);
    printf("---------------\n");

    line = get_next_line(fd2);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd3);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd1);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd2);
    printf("%s", line);
    printf("---------------\n");
    free(line);

    line = get_next_line(fd3);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    close(fd1);
    close(fd2);
    close(fd3);
    return 0;
}