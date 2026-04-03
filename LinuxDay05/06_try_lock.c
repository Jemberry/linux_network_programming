#include <my_header.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void *thread_func(void *arg)
{
    //子线程先上2锁
    int ret = pthread_mutex_lock(&lock2);
    THREAD_ERROR_CHECK(ret, "son pthread_mutex_lock2");

    printf("----\n");
    sleep(1);
    printf("--- over \n");
    //子线程再上1锁
    ret = pthread_mutex_trylock(&lock1);
    printf("ret : %d\n", ret);
    THREAD_ERROR_CHECK(ret, "son pthread_mutex_trylock1");

    //访问的共享资源
    printf("I am son\n");

    //先让子线程解锁1锁
    ret = pthread_mutex_unlock(&lock1);
    THREAD_ERROR_CHECK(ret, "son pthread_mutex_unlock1");

    //先让子线程解锁2锁
    ret = pthread_mutex_unlock(&lock2);
    THREAD_ERROR_CHECK(ret, "son pthread_mutex_unlock2");

    pthread_exit((void *)NULL);
}

int main(int argc, char *argv[])
{
    //初始化互斥锁
    int ret = pthread_mutex_init(&lock1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

    ret = pthread_mutex_init(&lock2, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

    pthread_t thread_id;
    ret = pthread_create(&thread_id, NULL, thread_func, NULL);//创建了子线程
    THREAD_ERROR_CHECK(ret, "pthread_create");

    //先上1锁
    ret = pthread_mutex_lock(&lock1);
    THREAD_ERROR_CHECK(ret, "main pthread_mutex_lock1");

    printf("+++++\n");
    sleep(1);
    printf("+++++ over\n");
    //再上2锁
    ret = pthread_mutex_lock(&lock2);
    THREAD_ERROR_CHECK(ret, "main pthread_mutex_lock2");

    //这就是模拟的共享资源
    printf("I am main\n");

    //主线程解2锁
    ret = pthread_mutex_unlock(&lock2);
    THREAD_ERROR_CHECK(ret, "main pthread_mutex_unlock2");
    
    //主线程解1锁
    ret = pthread_mutex_unlock(&lock1);
    THREAD_ERROR_CHECK(ret, "main pthread_mutex_unlock1");


    ret = pthread_join(thread_id, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");

    //最后一步，需要回收锁的资源
    ret = pthread_mutex_destroy(&lock1);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy1");

    ret = pthread_mutex_destroy(&lock2);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy2");
    return 0;
}

