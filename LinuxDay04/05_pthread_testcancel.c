#include <my_header.h>
#include <pthread.h>

void *thread_func(void *arg)
{
    while(1)
    {
        pthread_testcancel();
    }
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

