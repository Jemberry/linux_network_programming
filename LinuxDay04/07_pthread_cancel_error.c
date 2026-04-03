#include <my_header.h>

void *thread_func(void *arg)
{
    //堆空间资源
    char *pp = (char *)malloc(10);
    strcpy(pp, "hello");

    //文件描述符资源
    int fd = open("./Makefile", O_RDONLY);

    sleep(3);
    printf("son\n");

    free(pp);
    close(fd);
    printf("son over\n");

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t thread_id;
    int ret = pthread_create(&thread_id, NULL, thread_func, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    sleep(1);
    printf("I am main\n");

    //如果不写pthread_cancel函数，让子线程自己正常结束，那么子线程的
    //资源会自己清理；但是如果主线程让子线程被动退出，有可能资源没有
    //来的急清理，就会导致资源的浪费
    ret = pthread_cancel(thread_id);
    printf("ret : %d\n", ret);
    THREAD_ERROR_CHECK(ret, "pthread_cancel");

    ret = pthread_join(thread_id, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    printf("over\n");

    return 0;
}

