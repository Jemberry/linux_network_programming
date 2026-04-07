#include <arpa/inet.h>
#include <my_header.h>

int main(int argc, char *argv[])
{
    char *ptmp = "192.168.100.100";//点分十进制，小端存储

    struct in_addr addr;
    inet_aton(ptmp, &addr);//点分十进制的字符串ip转换成了网络字节序的
                           //in_addr的十进制形式
    printf("十进制的地址 : %d\n", addr.s_addr);

    char *pc = inet_ntoa(addr);//将网络字节序的十进制转换为本机的点分十进制
                           //的ip
    printf("pc = %s\n", pc);
    return 0;
}

