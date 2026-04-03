#include <my_header.h>

// B
void func(int num)
{
    printf("signal num: %d \n", num);
    exit(0);
}

int main(int argc,char*argv[])
{
    signal(10, func);

    int pipe_read = open("1.pipe", O_RDONLY);
    int pipe_write = open("2.pipe", O_WRONLY);

    int pid_a;
    int pid_b = getpid();
    write(pipe_write, &pid_b, sizeof(int));
    read(pipe_read, &pid_a, sizeof(int));

    fd_set set;
    FD_ZERO(&set);

    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    while(1)
    {
        FD_SET(STDIN_FILENO, &set);
        FD_SET(pipe_read, &set);

        select(10, &set, NULL, NULL, &tv);

        if(FD_ISSET(STDIN_FILENO, &set))
        {
            char buf[60] = {0};
            bzero(buf, sizeof(buf));

            int res = read(STDIN_FILENO, buf, sizeof(buf));
            // 任意一个进程在标准输入收到输入1，给所有进程（通信双方）发送10号信号
            if(res == 2 && atoi(buf) ==1)
            {
                kill(pid_a, 10);
                kill(pid_b, 10);

                return 0;
            }

            write(pipe_write, buf, sizeof(buf));
        }

        if(FD_ISSET(pipe_read, &set))
        {
            char buf[60] = {0};
            bzero(buf, sizeof(buf));

            int res = read(pipe_read, buf, sizeof(buf));
            if(res == 0)
            {
                printf("对端关闭了管道 \n");
                break;
            }

            printf("A: %s \n", buf);

            tv.tv_sec = 10;
            tv.tv_usec = 0;
        }
        else
        {
            if(tv.tv_sec == 0)
            {
                printf("超时断开 \n");
                break;
            }
        }
    }

    close(pipe_read);
    close(pipe_write);
    return 0;
}
