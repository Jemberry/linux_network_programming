#include <my_header.h>

void func()
{
    printf("func\n");
    long num = 10;
    pthread_exit((void *)num);//会让线程提前执行结束，那么后面的代码不会执行
    printf("+++++\n");
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

    void *retval;
    ret = pthread_join(thread_id, &retval);
    THREAD_ERROR_CHECK(ret, "pthread_join");
    printf("over\n");

    //将等待的子线程中的状态获取之后，将其转换为正常的值
    long tmp  = (long)retval;
    printf("tmp : %ld\n", tmp);

    return 0;
}

