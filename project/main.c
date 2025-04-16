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
    int fd = open("hello.txt", O_RDONLY);
    //fd = 0;
    char *line = get_next_line(fd);
    printf("%s", line);
    free (line);
    printf("---------------\n");

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free(line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free(line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);

    system("leaks a.out");

    close(fd);
    return 0;
}
