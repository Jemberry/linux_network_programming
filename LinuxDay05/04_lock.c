#include <my_header.h>


int main(int argc, char *argv[])
{
    //定义全局的锁变量
    pthread_mutex_t lock;

    //初始化互斥锁
    int ret = pthread_mutex_init(&lock, NULL);
    printf("ret : %d\n", ret);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");

    //上锁
    ret = pthread_mutex_lock(&lock);
    printf("ret : %d\n", ret);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_lock");
    
    /* //连续两次上锁 */
    /* ret = pthread_mutex_lock(&lock); */
    /* printf("ret : %d\n", ret); */
    /* THREAD_ERROR_CHECK(ret, "pthread_mutex_lock"); */

    //重要的代码

    //解锁
    ret = pthread_mutex_unlock(&lock);
    printf("ret : %d\n", ret);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock");

    //10gcc  4gcc n + gcc 一次注释(解注释)多行
    /* //一次上锁，连续两次解锁 */
    /* ret = pthread_mutex_unlock(&lock); */
    /* printf("ret : %d\n", ret); */
    /* THREAD_ERROR_CHECK(ret, "pthread_mutex_unlock"); */

    //最后一步，需要回收锁的资源
    ret = pthread_mutex_destroy(&lock);
    printf("ret : %d\n", ret);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_destroy");
    return 0;
}

