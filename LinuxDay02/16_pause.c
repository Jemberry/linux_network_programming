#include <my_header.h>

void func(int num)
{
    printf("num : %d\n", num);
}

int main(int argc, char *argv[])
{
    signal(2, func);

    printf("pause begin\n");
    pause();
    printf("pause over\n");

    
    while(1);
    return 0;
}

