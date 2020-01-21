#include <stdio.h>

void recursive(int a)
{
    printf("%d\r\n", a);
    if (a < 10)
    {
        recursive(a + 1);
    }
    printf("%d\n", a);
}

int main(void)

{
    recursive(0);
    return 0;
}