#include <my_header.h>

void func(int num)
{
    printf("num : %d\n", num);
}

int main(int argc, char *argv[])
{
    struct sigaction act, oldact;
    //清空act
    memset(&act, 0, sizeof(act));
    
    //信号处理函数
    act.sa_handler = func;
    //信号处理函数只会生效一次
    act.sa_flags = SA_RESETHAND;

    sigaction(2, &act, &oldact);

    printf("beign while\n");
    while(1);
    return 0;
}

