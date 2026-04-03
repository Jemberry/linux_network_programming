#include <my_header.h>

void free_func(void *p)
{
    printf("free_func\n");
    char *ptmp = (char *)p;
    free(ptmp);
    ptmp = NULL;
}

void close_func(void *p)
{
    printf("close_func\n");
    int *fd = (int *)p;
    close(*fd);
}

void *thread_func(void *arg)
{
    //堆空间资源
    char *pp = (char *)malloc(10);
    strcpy(pp, "hello");
    pthread_cleanup_push(free_func, pp);

    //文件描述符资源
    int fd = open("./Makefile", O_RDONLY);
    pthread_cleanup_push(close_func, (void *)&fd);

    sleep(3);
    printf("son\n");
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);

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

    ret = pthread_cancel(thread_id);
    printf("ret : %d\n", ret);
    THREAD_ERROR_CHECK(ret, "pthread_cancel");

    ret = pthread_join(thread_id, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    printf("over\n");

    return 0;
}

