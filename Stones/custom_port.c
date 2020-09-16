#include <stdio.h>
#include <stdint.h>

#define EVAL(V...)     EVAL16(V)
#define EVAL1024(V...) EVAL512(EVAL512(V))
#define EVAL512(V...)  EVAL256(EVAL256(V))
#define EVAL256(V...)  EVAL128(EVAL128(V))
#define EVAL128(V...)  EVAL64(EVAL64(V))
#define EVAL64(V...)   EVAL32(EVAL32(V))
#define EVAL32(V...)   EVAL16(EVAL16(V))
#define EVAL16(V...)   EVAL8(EVAL8(V))
#define EVAL8(V...)    EVAL4(EVAL4(V))
#define EVAL4(V...)    EVAL2(EVAL2(V))
#define EVAL2(V...)    EVAL1(EVAL1(V))
#define EVAL1(V...)    V


#define test1 EVAL16("test")
#define test EVAL(test1)
int main(void)
{
    uint8_t a,b,c;
    

    printf(test1);
    printf(test);
}