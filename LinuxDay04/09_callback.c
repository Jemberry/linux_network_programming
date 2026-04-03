#include <my_header.h>

int func()
{
    printf("func\n");
    return 10;
}

int func2()
{
    printf("func2\n");
    return 20;
}

int main(int argc, char *argv[])
{
    //主动调用
    /* func(); */
    /* func2(); */

    int (*pFunc)();
    pFunc = func;
    printf("1111\n");
    pFunc();//这里就间接调用了func函数
    printf("2222\n");

    pFunc = func2;
    printf("3333\n");
    pFunc();//这里就间接调用了func2函数
    printf("4444\n");
    return 0;
}

