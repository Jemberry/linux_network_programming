#include <my_header.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int flag = 0 ;// 标记A有没有已经打印

void *func(void *p)
{
    pthread_mutex_lock(&lock);
    if(flag == 0)
    {
        pthread_cond_wait(&cond, &lock);
    }

    pthread_mutex_unlock(&lock);
    printf("Before B \n");
    sleep(3);
    printf("After B \n");

    return NULL;
}

int main(int argc,char*argv[])
{
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t son_id;
    pthread_create(&son_id, NULL, func, NULL);

    printf("Before A \n");
    sleep(3);
    printf("After A \n");

    pthread_mutex_lock(&lock);
    flag = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    pthread_join(son_id, NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
