#include <my_header.h>

void *thread_func(void *arg)
{
    printf("I am son\n");
    
    long num = 100;
    return (void *)num;
}

int main(int argc, char *argv[])
{
    pthread_t thread_id;
    //创建子线程
    int ret = pthread_create(&thread_id, NULL, thread_func, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    printf("I am main\n");

    void *retval;
    ret = pthread_join(thread_id, &retval);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    printf("over\n");

    long ptmp = (long)retval;

    printf("ptmp : %ld\n", ptmp);

    return 0;
}

