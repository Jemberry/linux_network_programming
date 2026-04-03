#include <my_header.h>

void *thread_func(void *arg)
{
    printf("I am son\n");
    
    int *pInt = (int *)malloc(4);
    *pInt = 10;

    return (void *)pInt;
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

    int *ptmp = (int *)retval;;

    printf("ptmp : %d\n", *ptmp);

    return 0;
}

