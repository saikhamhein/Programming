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

int main(int argc, char *argv[])

{
    int i;
    if (argc >= 2)
    {
        printf("The arguments supplied are:\n");
        for (i = 1; i < argc; i++)
        {
            printf("%d \t", *argv[i] - 48);
        }
    }
    else
    {
        printf("argument list is empty.\n");
    }
    recursive(*argv[1] - 48);
    return 0;
}