#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("hello.txt", O_RDONLY);
    char *line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");
    free (line);
    line = get_next_line(fd);
    printf("%s", line);
    printf("---------------\n");

    free (line);
    close(fd);
}