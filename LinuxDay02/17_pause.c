#include <my_header.h>
#include <signal.h>

void func(int num)
{
    printf("num : %d\n", num);
}

int main(int argc, char *argv[])
{
    signal(2, func);

    sigset_t set, oldset;
    sigemptyset(&set);
    sigaddset(&set, 2);

    sigprocmask(SIG_BLOCK, &set, &oldset);
    //--------
    //这里有一段重要的代码,不想让这个重要代码被2号信号打断
    //这段代码对2号信号屏蔽
    sleep(10);
    printf("sleep over\n");
    //--------这段代码执行结束了，需要接触2号信号的屏蔽
    sigprocmask(SIG_UNBLOCK, &set, &oldset);

    printf("pause begin\n");
    pause();
    printf("pause over\n");

    
    printf("while begin\n");
    while(1);
    printf("while over\n");
    return 0;
}

