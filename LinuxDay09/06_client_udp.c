#include <my_header.h>

int main(int argc, char *argv[])
{
    char *ip = "192.168.100.128";
    char *port = "12345";

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(fd, -1, "socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);

    //将数据发送给客户端
    sendto(fd, "hello", 5, 0, (struct sockaddr *)&addr, sizeof(addr));

    //----数据的收发
    char buf[50] = {0};
    recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
    printf("recv from server: %s\n", buf);

    close(fd);

    return 0;
}

