#include <my_header.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void func(int num)
{
    printf("num : %d\n", num);
}

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    if(0 == pid)
    {
        signal(2, func);
        //子进程
        while(1)
        {
            sleep(1);
            printf("while\n");
        }
    }
    else
    {
        sleep(10);
        //父进程
        kill(pid, 2);
    }
    return 0;
}

