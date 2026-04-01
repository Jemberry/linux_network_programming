#include <my_header.h>

void func(int num)
{
    printf("num : %d\n", num);
    printf("sleep begin\n");
    sleep(10);
    printf("sleep over\n");
}

int main(int argc, char *argv[])
{
    struct sigaction act, oldact;
    //清空act
    memset(&act, 0, sizeof(act));
    
    //信号处理函数
    act.sa_handler = func;
    //同一个信号可以再次触发（连续触发）
    act.sa_flags = SA_NODEFER;

    sigaction(2, &act, &oldact);

    printf("beign while\n");
    while(1);
    return 0;
}

