#include <my_header.h>

void func(int num)
{
    printf("signal %d begin \n", num);
    sleep(10);

    sigset_t set;
    sigemptyset(&set);
    sigpending(&set);

    if(sigismember(&set, 2))
    {
        printf("2号信号未决 \n");
    }

    sigemptyset(&set);
    sigset_t oldset;
    sigemptyset(&oldset);

    // 目的: 获取当前的mask掩码状态 (通过 oldset )
    sigprocmask(SIG_UNBLOCK, &set, &oldset);
    if(sigismember(&oldset, 2))
    {
        printf("2号信号在掩码中被设置了阻塞 \n");
    }

    if(sigismember(&oldset, 3))
    {
        printf("3号信号在掩码中被设置了阻塞 \n");
    }

    printf("signal %d over \n", num);
}

int main(int argc, char *argv[])
{
    signal(2, func);
    while(1);
    return 0;
}

