#include <my_header.h>

void func(int num)
{
    printf("num : %d\n", num);
}

int main(int argc, char *argv[])
{
    //signal函数就是一个非常简单的函数，可以设置
    //信号的处理方式
    signal(2, func);

    sigset_t set, oldset;
    sigemptyset(&set);
    sigaddset(&set, 2);

    //全局屏蔽2号信号(sigprocmask函数本身不是阻塞函数)
    sigprocmask(SIG_BLOCK, &set, &oldset);
    sleep(10);
    printf("sleep over\n");
    //接触对2号信号的屏蔽
    sigprocmask(SIG_UNBLOCK, &set, &oldset);

    printf("while\n");
    while(1);
    return 0;
}

