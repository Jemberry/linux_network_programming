#include <bits/types/siginfo_t.h>
#include <my_header.h>
#include <unistd.h>

void func(int num, siginfo_t *siginfo, void *p)
{
    printf("num : %d\n", num);
    printf("func pid : %d\n", getpid());
    printf("xxx pid : %d\n", siginfo->si_pid);
}

int main(int argc, char *argv[])
{

    struct sigaction act, oldact;
    //清空act
    memset(&act, 0, sizeof(act));
    
    //信号处理函数
    //在C语言中，数组名是数组的入口地址；
    //函数名就是函数的入口地址
    act.sa_sigaction = func;

    //设置标志位位SA_SIGINFO
    act.sa_flags = SA_SIGINFO;

    sigaction(2, &act, &oldact);

    printf("beign while\n");
    while(1);
    return 0;
}

