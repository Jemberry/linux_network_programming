#include <my_header.h>
#include <signal.h>

void func(int num)
{
    printf("num : %d\n", num);
    alarm(1);
}

int main(int argc, char *argv[])
{
    signal(SIGALRM, func);
    //设计了定时器（时间就是10s）
    alarm(10);

    printf("while begin\n");
    while(1);
    printf("while over\n");
    return 0;
}

