#include <asm-generic/socket.h>
#include <my_header.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *ip = "192.168.100.128";
    char *port = "12345";

    //创建文件描述符
    int listen_fd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(listen_fd, -1, "socket");

    //绑定服务器的ip与端口号
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));//初始化addr

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);//本机字节序转换为网络字节序
    addr.sin_port = htons(atoi(port));

    fd_set set;
    FD_ZERO(&set);

    while(1)
    {
        FD_SET(STDIN_FILENO, &set);
        FD_SET(listen_fd, &set);

        int nready = select(10, &set, NULL, NULL, NULL);
        printf("nready: %d\n", nready);

        if(FD_ISSET(STDIN_FILENO, &set))
        {
            char buf[50] = {0};
            read(STDIN_FILENO, buf, sizeof(buf));
            int cnt = sendto(listen_fd, buf, sizeof(buf), 0, 
                             (struct sockaddr *)&addr, sizeof(addr));
            printf("send cnt: %d\n", cnt);
        }

        if(FD_ISSET(listen_fd, &set))
        {
            char buf[50] = {0};
            int cnt = recvfrom(listen_fd, buf, sizeof(buf), 0
                               , NULL, NULL);
            printf("recv cnt: %d\n", cnt);
            printf("recv buf: %s\n", buf);
        }
    }
    //最后就应该将所有的文件描述符关闭
    close(listen_fd);

    return 0;
}

