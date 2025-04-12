#include <stdio.h>
#include <stdlib.h>

// int main(void)
// {
//     static char array[10] = "abcdefghi\0";
//     int i = 0;

//     printf("%s\n", array);
//     while (i < 10 - 2)
//     {
//         array[i] = array[i + 2];
//         i++;
//     }
//     printf("%s\n", array);

//     return 0;
// }

int main(void)
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    char *mem = (char *)malloc(sizeof(char) * 10);

    printf("%zd\n", sizeof(mem));

    return 0;
}