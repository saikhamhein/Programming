#include <stdio.h>
#include <stdint.h>

int main()
{
    uint8_t hello_world[] = "hello_world";
    int nest_fun(uint8_t * ptr)
    {
        printf(ptr);
    }
    nest_fun(hello_world);
}
