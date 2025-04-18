#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>


// ccw -D BUFFER_SIZE=1
// ccw -D BUFFER_SIZE=10
// ccw -D BUFFER_SIZE=9999
// ccw -D BUFFER_SIZE=1000000
// ccw -D BUFFER_SIZE=0
// ccw -D BUFFER_SIZE=-1
// ccw -D BUFFER_SIZE=999999999

// input/single_char.txt
// input/single_line.txt
// input/multiple_line.txt
// input/empty.txt
// input/single_nl.txt
// input/multiple_nl.txt
// input/long_line.txt
// input/long_multiple_line.txt

int main(void)
{
    int fd = open("input/hello.txt", O_RDONLY);
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

    //system("leaks a.out");

    close(fd);
    return 0;
}
