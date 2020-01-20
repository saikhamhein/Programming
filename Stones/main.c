#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include "DigitalStopWatch.h"
void Init_State(void);
void Red_State(void);
void Yellow_State(void);
void Green_State(void);

uint32_t some_32bit_data = 0;
struct StateMachine_t
{
    void (*next_State)(void);
    void (*current_State)(void);
    void *information; // This ptr serve as general purpose ptr
};

typedef struct StateMachine_t StateMachine_t;
StateMachine_t StateMachine_Structure = {Init_State, Init_State, &some_32bit_data}; //
StateMachine_t *SMPtr = &StateMachine_Structure;

uint8_t some_data_array[] = {"Hello World!\r\n\n"};

void Init_State(void)
{
    uint32_t *ptr;
    ptr = (uint32_t *)SMPtr->information;
    SMPtr->current_State = Init_State;
    SMPtr->next_State = Red_State;
    /*current state is resonpsible for passing argument to the next state before switching
    in this case pointer to array for the function Red_State*/
    SMPtr->information = some_data_array;
    printf("Init State \r\n");
    printf("%d \r\n\n", *ptr);
}

void Red_State(void)
{ /*the function accepting the argument must convert the void pointer to correct ptr type*/
    /*in this case cast void pointer to uint8_t */
    uint8_t *ptr;
    ptr = (uint8_t *)SMPtr->information;
    SMPtr->current_State = Red_State;
    SMPtr->next_State = Yellow_State;
    /*before switching the next state SMPtr->information must be updated with data for the next state*/
    /*in this case the state it need to switch after it finish processing*/
    /*We gonna switch to the Green State after the yellow state*/
    /*In this case yellow state must know what kind of data green state was expecting*/
    SMPtr->information = Green_State;
    printf("Red State  \r\n");
    printf(ptr);
}

void Yellow_State(void)
{
    SMPtr->current_State = Yellow_State;
    SMPtr->next_State = SMPtr->information;
    /*in yellow state doesnt pass data to the next state.In this case it will be green */
    /*in this the SMPtr->information is set to NULL*/
    SMPtr->information = NULL;
    printf("Yellow State \r\n\n");
}

void Green_State(void)
{
    SMPtr->current_State = Green_State;
    /*this state is a counter*/
    some_32bit_data++;
    SMPtr->next_State = Init_State;
    /*data for Init_state*/
    /*Init_state is expecting 32bit data */
    SMPtr->information = &some_32bit_data;
    printf("Green State \r\n\n");
}

int main()
{
    int i = 0;

    for (i = 0; i <= 9; i++)
    {
        SMPtr->next_State();
    }

    return 0;
}
