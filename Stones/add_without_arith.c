#include <stdio.h>

int add(int x, int y)
{
    //const char* const p =(const char*) x;
    char* p = (char *)x;
    return (int) &p[y];
}



int main(void)
{
    int x;
    x=add(2,3);
    printf("%d",x);
    return 0;
}