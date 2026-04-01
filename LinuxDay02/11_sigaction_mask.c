#include <my_header.h>
#include <signal.h>
#include <unistd.h>

void func(int num)
{
    printf("num : %d\n", num);
    printf("sleep begin\n");
    sleep(10);
    printf("sleep over\n");
}

int main(int argc, char *argv[])
{
    //在触发2号信号的过程中，如果来了3号好信号
    //3号信号会被屏蔽
    struct sigaction act, oldact;
    //清空act
    memset(&act, 0, sizeof(act));
    
    //信号处理函数
    act.sa_handler = func;

    //设置掩码mask
    sigset_t mask;
    sigemptyset(&mask);//清空
    sigaddset(&mask, 3);
    act.sa_mask = mask;

    sigaction(2, &act, &oldact);

    printf("beign while\n");
    while(1);
    return 0;
}

