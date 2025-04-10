#include <stdio.h>

int main(void)
{
    static char array[10] = "abcdefghi\0";
    int i = 0;

    printf("%s\n", array);
    while (i < 10 - 2)
    {
        array[i] = array[i + 2];
        i++;
    }
    printf("%s\n", array);

    return 0;
}
