#include <my_header.h>

void *thread_func(void *arg)
{
    printf("I am son\n");
    while(1);

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread_id;
    //创建子线程
    int ret = pthread_create(&thread_id, NULL, thread_func, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    printf("I am main\n");

    //主线程调用pthread_join的时候，会等子线程，子线程不执行完毕
    //主线程就卡在这里
    pthread_join(thread_id, NULL);
    //因为子线程不退出，所以主线程一直等着子线程，最终的结果是
    //整个进程卡死了

    printf("over\n");


    return 0;
}

