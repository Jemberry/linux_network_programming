#include <my_header.h>

void func(int num)
{
    printf("num: %d\n", num);
}

int main(int argc, char *argv[])
{
    signal(2, func);
    //n + shift + k
    unsigned int ret = sleep(20);
    printf("ret: %u\n", ret);
    
    return 0;
}

