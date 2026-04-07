#include <my_header.h>

int main(int argc, char *argv[])
{
    int num = 0x75767778;//这是16进制
    char *ptmp = (char *)&num;
    //0x78 = 7 * 16 + 8 = 112 + 8 = 120 ASCII x 小端法
    //0x75 = 7 * 16 + 5 = 112 + 5 = 117 ASCII u 大端法
    printf("%c\n", *ptmp);

    int a = htonl(num);
    char *pa =  (char *)&a;
    printf("%c\n", *pa);

    return 0;
}

