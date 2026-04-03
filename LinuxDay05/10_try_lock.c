#include <my_header.h>

pthread_mutex_t lock1;

void *thread_func(void *arg)
{
    int ret = 0;
    while(1)
    {
        //子线程再上1锁
        ret = pthread_mutex_trylock(&lock1);
        if(0 == ret)
        {
            break;
        }

    }
    //访问的共享资源
    printf("I am son\n");
    //先让子线程解锁1锁
    ret = pthread_mutex_unlock(&lock1);
    THREAD_ERROR_CHECK(ret, "son pthread_mutex_unlock1");

    pthread_exit((void *)NULL);
}

int main(int argc, char *argv[])
{
    //初始化互斥锁
    int ret = pthread_mutex_init(&lock1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

    pthread_t thread_id;
    ret = pthread_create(&thread_id, NULL, thread_func, NULL);//创建了子线程
    THREAD_ERROR_CHECK(ret, "pthread_create");

    ret = pthread_mutex_lock(&lock1);
    THREAD_ERROR_CHECK(ret, "main pthread_mutex_lock1");

    sleep(100);

    //这就是模拟的共享资源
    printf("I am main\n");
    
    ret = pthread_mutex_unlock(&lock1);
    THREAD_ERROR_CHECK(ret, "main pthread_mutex_unlock1");

    ret = pthread_join(thread_id, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");

    //最后一步，需要回收锁的资源
    ret = pthread_mutex_destroy(&lock1);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy1");

    return 0;
}

