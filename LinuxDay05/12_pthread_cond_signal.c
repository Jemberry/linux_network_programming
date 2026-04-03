#include <my_header.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;

void *thread_func(void *arg)
{
    sleep(1);
    //子线程再上
    int ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");

    //访问的共享资源
    printf("I am son\n");

    //子线程在将共享资源访问完毕之后，就可以将主线程唤醒
    ret = pthread_cond_signal(&cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_signal");

    //写这一句的原因，就是为了看子线程唤醒主线程后，主线程
    //是不能立马从pthread_cond_wait上返回的，只要子线程
    //释放了互斥锁之后，主线程才能抢到锁
    sleep(100);

    //先让子线程解锁
    ret = pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret, "son pthread_mutex_unlock1");

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
    pthread_t thread_id;
    ret = pthread_create(&thread_id, NULL, thread_func, NULL);//创建了子线程
    THREAD_ERROR_CHECK(ret, "pthread_create");

    ret = pthread_mutex_lock(&lock);
    THREAD_ERROR_CHECK(ret, "main pthread_mutex_lock1");

    printf("begin wait\n");
    //因为没有满足条件，而睡眠
    ret = pthread_cond_wait(&cond, &lock);
    THREAD_ERROR_CHECK(ret, "main pthread_cond_wait");

    //共享资源
    printf("I am main condition ok\n");

    //解锁
    ret = pthread_mutex_unlock(&lock);
    THREAD_ERROR_CHECK(ret, "main pthread_mutex_unlock1");

    //主线程等子线程
    ret = pthread_join(thread_id, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");

    //最后一步，需要回收锁的资源
    ret = pthread_mutex_destroy(&lock);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy1");

    //条件变量的销毁
    ret = pthread_cond_destroy(&cond);
    THREAD_ERROR_CHECK(ret, "pthread_cond_destroy");

    return 0;
}

