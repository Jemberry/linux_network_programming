#include <my_header.h>
#include <sys/time.h>

//定义全局的锁变量
pthread_mutex_t lock;
int gCnt = 0;

void *thread_func(void *arg)
{
    for(int idx = 0; idx < 1000000; ++idx)
    {
        /* int ret = pthread_mutex_lock(&lock); */
        /* THREAD_ERROR_CHECK(ret, "pthread_mutex_lock"); */
        ++gCnt;
        /* ret = pthread_mutex_unlock(&lock); */
        /* THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock"); */
    }
    printf("I am son\n");

    pthread_exit((void *)NULL);
}

int main(int argc, char *argv[])
{
    struct timeval beg, end;
    gettimeofday(&beg, NULL);

    //初始化互斥锁
    int ret = pthread_mutex_init(&lock, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

    pthread_t thread_id;
    ret = pthread_create(&thread_id, NULL, thread_func, NULL);//创建了子线程
    THREAD_ERROR_CHECK(ret, "pthread_create");

    //共享资源gCnt进行改写操作
    for(int idx = 0; idx < 1000000; ++idx)
    {
        //上锁
        /* ret = pthread_mutex_lock(&lock); */
        /* THREAD_ERROR_CHECK(ret, "pthread_mutex_lock"); */
        ++gCnt;//(1)将gCnt的值从内存读到寄存器中
               //(2)CPU会修改gCnt的值
               //(3)将修改之后的值传到内存中
        /* ret = pthread_mutex_unlock(&lock); */
        /* THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock"); */
    }

    printf("I am main\n");

    ret = pthread_join(thread_id, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    printf("gCnt: %d\n", gCnt);


    //最后一步，需要回收锁的资源
    ret = pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy");

    gettimeofday(&end, NULL);
    printf("time : %ld\n", (end.tv_sec - beg.tv_sec) * 1000000 
                           + (end.tv_usec - beg.tv_usec));

    //y/d + 目标行号 + G 多行的拷贝/多行的删除
    return 0;
}

