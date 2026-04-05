#include <my_header.h>

pthread_mutex_t my_lock;
pthread_cond_t cond;

int flag = 0; // 某个线程检测flag==0, 说明自己先上线的

//AC线程
void * funcAC(void *p)
{
    pthread_mutex_lock(&my_lock);
    if(flag == 0)
    {
        // 假设AC先执行
        flag = 1;
        printf("A \n");
        pthread_cond_wait(&cond, &my_lock);
        printf("C \n");
        pthread_mutex_unlock(&my_lock);
    }
    else
    {
        // B先运行
        printf("A \n");
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond, &my_lock);
        printf("C \n");
        pthread_mutex_unlock(&my_lock);
    }
    return NULL;
}

//B线程
void * funcB(void *p)
{
    pthread_mutex_lock(&my_lock);
    if(flag == 0)
    {
        // B先上线获取锁
        flag = 1;
        pthread_cond_wait(&cond, &my_lock);
        printf("B \n");
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&my_lock);
    }
    else
    {
        // AC先上线, B后执行
        printf("B \n");
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&my_lock);
    }
    return NULL;
}

int main(int argc,char*argv[])
{
    pthread_mutex_init(&my_lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t sonac, sonb;
    //创建了AC线程与B线程,因为线程的执行是随机的
    //谁先执行谁后执行是不清楚
    pthread_create(&sonac, NULL, funcAC, NULL);
    pthread_create(&sonb, NULL, funcB, NULL);

    pthread_join(sonac, NULL);
    pthread_join(sonb, NULL);

    pthread_mutex_destroy(&my_lock);
    pthread_cond_destroy(&cond);

    return 0;
}
