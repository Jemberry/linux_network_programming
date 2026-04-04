#include <my_header.h>
#include <pthread.h>

void *thread_func(void *arg)
{
    printf("son thread id : %ld\n", pthread_self());

    pthread_exit((void *)NULL);
}

int main(int argc, char *argv[])
{
    //线程属性类型创建的变量
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //设置分离属性
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t thread_id;
    //此时创建子线程的时候，设置了attr属性，也就是分离属性
    int ret = pthread_create(&thread_id, &attr, thread_func, NULL);
    printf("ret : %d\n", ret);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    /* sleep(1); */
    printf("main thread id : %ld\n", pthread_self());

    //主线程等待子线程
    ret = pthread_join(thread_id, NULL);
    printf("ret : %d\n", ret);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    return 0;
}

