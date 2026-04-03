#include <my_header.h>

void func()
{
    printf("func\n");
    return;
}

void *thread_func(void *arg)
{
    printf("I am son\n");
    func();
    printf("func over int thread_func\n");
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread_id;
    //创建子线程
    int ret = pthread_create(&thread_id, NULL, thread_func, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create");

    printf("I am main\n");

    ret = pthread_join(thread_id, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    printf("over\n");

    return 0;
}

