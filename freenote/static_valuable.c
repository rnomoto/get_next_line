#include <stdio.h>

void static_valuable(void)
{
    static char *buf;

    printf("%s\n", buf);
}


int main(void)
{
    static_valuable();

    return 0;
}
