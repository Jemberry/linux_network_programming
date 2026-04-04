#include <my_header.h>

char *fun()
{
    static char p[20] = {0};
    for(int i = 0; i < 20; i++)
    {
        if(p[i] == 0)
        {
            p[i] = 'a';
            break;
        }
    } 
    return p;
} 

int func()
{
    int a = 10;
    ++a;
    return a;
}

int main(int argc,char* argv[])
{
    /* char *p1 = fun(); */
    /* printf("p = %s \n", p1); */
    /* //第二次进入这个fun函数 */
    /* char *p2 = fun(); */
    /* printf("p = %s \n", p2); */
    int x = func();
    printf("x = %d\n", x);
    int y = func();
    printf("y = %d\n", y);

    return 0;
}

