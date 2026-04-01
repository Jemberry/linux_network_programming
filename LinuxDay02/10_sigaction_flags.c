#include <my_header.h>
#include <unistd.h>

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
    //使信号打断的系统调用自动重新调用
    act.sa_flags = SA_RESTART;

    sigaction(2, &act, &oldact);

    char buf[100] = {0};
    read(STDIN_FILENO, buf, sizeof(buf));
    printf("read over\n");

    /* printf("beign while\n"); */
    /* while(1); */
    return 0;
}

