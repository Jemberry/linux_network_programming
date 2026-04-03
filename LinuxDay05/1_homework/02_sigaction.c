#include <my_header.h>

void func(int num)
{
    printf("func run \n");
    sleep(10);

    // 2号信号的信号处理函数中，使用sigpending函数判断一下有没有3号信号处于未决状态
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);
    if(sigismember(&pending, 3))
    {
        printf("在当前的2号信号处理逻辑中, 有一个3号信号已经到啦, 被屏蔽了 \n");
    }

    printf("func over \n");
}

int main(int argc,char*argv[])
{
    struct sigaction act , old;
    memset(&act, 0, sizeof(act));
    memset(&old, 0, sizeof(old));

    act.sa_handler = func;
    //重启系统调用(如下read函数)
    act.sa_flags = SA_RESTART;

    //设置处理2号信号时阻塞3号信号
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, 3);
    act.sa_mask = set;

    sigaction(2, &act, &old);
    char buf[60] = {0};
    read(STDIN_FILENO, buf, sizeof(buf));
    printf("buf: %s \n", buf);

    return 0;
}
