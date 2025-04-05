#include <stdio.h>

void add(int num)
{
    static int  static_num;
    int non_static_num;

    non_static_num = 0; //static int doesn't have to initiate !?
    static_num += num;
    non_static_num += num;
    printf("    static_num: %d\n", static_num);
    printf("non_static_num: %d\n", non_static_num);
    printf("==================\n");
}

int main(void)
{
    add(3);
    add(3);
    add(3);

    return 0;
}