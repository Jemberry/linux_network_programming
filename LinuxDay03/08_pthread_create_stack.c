#include <my_header.h>

void *thread_func(void *arg)
{
    sleep(1);//这里的写法就是为了控制时序，让func函数中的num局部变量提前销毁
             //那么在thread_func函数中访问num就是访问了已经销毁的局部变量
             //那么肯定就有问题了
    printf("I am son\n");

    int *pint = (int *)arg;
    *pint = 30;

    printf("*pint : %d\n", *pint);

    return NULL;
}

void func()
{
    int num = 10;//主线程中的10

    pthread_t thread_id;
    //pthread_create的第四个参数可以将值传递给线程入口函数
    int ret = pthread_create(&thread_id, NULL, thread_func, (void *)&num);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    /* sleep(3); */
}

int main(int argc, char *argv[])
{
    func();
    printf("I am main\n");
    sleep(5);//为了让主线程等着子线程,如果不写，子线程都可能没有机会执行进程
             //就结束了

    return 0;
}

