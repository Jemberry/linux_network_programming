#include <my_header.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    //水平触发式默认的模式,监听STDIN_FILENO文件描述符，只要通过终端
    //输入数据，就可以触发这个文件描述符可读
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");

    struct epoll_event evt;
    evt.events = EPOLLIN;//监听读事件
    evt.data.fd = STDIN_FILENO;//监听的文件描述符
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &evt);
    ERROR_CHECK(ret, -1, "epoll_ctl add");

    while(1)
    {
        //对于水平触发而言，只要文件描述符可读（在这里就是缓冲区中有数据
        //那么，就一直可读，一直将缓冲区中的数据读空）
        struct epoll_event lst[2];
        int nready = epoll_wait(epfd, lst, 2, -1);
        ERROR_CHECK(nready, -1, "epoll_wait");
        printf("nready: %d\n", nready);
        printf("----------------------------\n\n" );

        for(int idx = 0; idx < nready; ++idx)
        {
            int fd = lst[idx].data.fd;

            if(fd == STDIN_FILENO)
            {
                char buf[2] = {0};
                read(fd, buf, sizeof(buf));
                printf("buf:%s\n", buf);
            }
        }

    }
    return 0;
}

