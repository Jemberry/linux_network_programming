#include <my_header.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;

void *thread_funcA(void *arg)
{
    sleep(1);
    //子线程再上
    int ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lockA");

    printf("sonA wait begin\n");
    ret = pthread_cond_wait(&cond, &lock);
    THREAD_ERROR_CHECK(ret, "pthread_cond_waitA");
    //访问的共享资源
    printf("sonA wait end\n");

    //访问的共享资源
    printf("I am sonA\n");

    //先让子线程解锁
    ret = pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret, "son pthread_mutex_unlockA");

    pthread_exit((void *)NULL);
}

void *thread_funcB(void *arg)
{
    sleep(1);
    //子线程再上
    int ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lockB");

    printf("sonB wait begin\n");
    ret = pthread_cond_wait(&cond, &lock);
    THREAD_ERROR_CHECK(ret, "pthread_cond_waitB");
    printf("sonB wait end\n");

    //访问的共享资源
    printf("I am sonB\n");

    //先让子线程解锁
    ret = pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret, "son pthread_mutex_unlockB");

    pthread_exit((void *)NULL);
}

int main(int argc, char *argv[])
{
    //初始化互斥锁
    int ret = pthread_mutex_init(&lock, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

    //初始化条件变量
    ret = pthread_cond_init(&cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");

    //创建子线程
    pthread_t thread_idA, thread_idB;
    ret = pthread_create(&thread_idA, NULL, thread_funcA, NULL);//创建了子线程A
    THREAD_ERROR_CHECK(ret, "pthread_createA");

    ret = pthread_create(&thread_idB, NULL, thread_funcB, NULL);//创建了子线程B
    THREAD_ERROR_CHECK(ret, "pthread_createB");

    //共享资源
    printf("I am main condition ok\n");
    sleep(5);

    //将所有等待在条件变量上的线程都唤醒
    ret = pthread_cond_broadcast(&cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_broadcast");

    //主线程等子线程A
    ret = pthread_join(thread_idA, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_joinA");

    //主线程等子线程B
    ret = pthread_join(thread_idB, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_joinB");

    //最后一步，需要回收锁的资源
    ret = pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy1");

    //条件变量的销毁
    ret = pthread_cond_destroy(&cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_destroy");

    return 0;
}

