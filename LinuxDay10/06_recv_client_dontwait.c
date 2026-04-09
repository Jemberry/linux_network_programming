#include <my_header.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{
    char *ip = "192.168.100.128";
    char *port = "12345";

    //创建文件描述符
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listen_fd, -1, "socket");

    //绑定服务器的ip与端口号
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));//初始化addr

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);//本机字节序转换为网络字节序
    addr.sin_port = htons(atoi(port));

    //调用connect函数进行三次握手
    int ret = connect(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");

    //客户端与服务器进行数据的收发
    //客户端给服务器发送数据
    printf("sleep before\n");
    sleep(30);
    int cnt = send(listen_fd, "hello", 5, 0);
    printf("read cnt: %d\n", cnt);

    while(1);
    //关闭文件描述符(意味着执行了四次挥手)
    close(listen_fd);
    return 0;
}

