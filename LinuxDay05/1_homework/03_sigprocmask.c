#include <my_header.h>

int main(int argc,char*argv[])
{
    // 通过sigprocmask阻塞2号信号
    sigset_t set, old;
    sigemptyset(&set);
    sigemptyset(&old);
    sigaddset(&set, 2);
    sigprocmask(SIG_BLOCK, &set, &old);

    sleep(5);
    // 在睡眠后，解除阻塞之前，通过sigpending检测是否有信号挂起。
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);

    if(sigismember(&pending, 2))
    {
        printf("2号信号未决\n");
    }

    // 睡眠5秒后，解除阻塞
    sigprocmask(SIG_UNBLOCK, &set, &old);

    while(1);

    return 0;
}
