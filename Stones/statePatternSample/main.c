#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct StateMachine_t StateMachine_t;
struct StateMachine_t
{
    void (*next_State)   (StateMachine_t*);
    void (*current_State)(StateMachine_t*);
    void *infoPtr;
};

void Init_State  (StateMachine_t * obj);
void Red_State   (StateMachine_t * obj);
void Yellow_State(StateMachine_t * obj);
void Green_State (StateMachine_t * obj);
void Loop_State  (StateMachine_t * obj);

StateMachine_t StateMachine_Structure = {Init_State,Init_State,NULL};
StateMachine_t * SMPtr = &StateMachine_Structure;
#define TERMINATION_STATE "Termination State"
void Loop_State(StateMachine_t * obj)
{
    static const char LoopInfo[] = "Passing Info from Loop State";
    if( obj == NULL )
        return;
    if( obj->infoPtr-- )
    {
        printf("Loop Cnt = %d\r\n",(int)SMPtr->infoPtr);
    }
    else
    {
        obj->infoPtr = (char*)LoopInfo;
        obj->current_State = Loop_State;
        obj->next_State = Red_State;
    }
}

void Init_State(StateMachine_t * obj)
{    if( obj == NULL )
        return;
    obj->current_State = Init_State;
    obj->next_State = Loop_State;
    obj->infoPtr = (int*)10;
    printf("Init State\r\n");
}

void Red_State(StateMachine_t * obj)
{    if( obj == NULL )
        return;
    if( obj != NULL )
    {
        printf("%s ",(char*)SMPtr->infoPtr);
        SMPtr->infoPtr = NULL;
    }
    printf("Red State\r\n");
    obj->current_State = Red_State;
    obj->next_State = Yellow_State;
}

void Yellow_State(StateMachine_t * obj)
{    if( obj == NULL )
        return;
    obj->current_State = Yellow_State;
    obj->next_State = Green_State;
    obj->infoPtr = (char*)TERMINATION_STATE;
    printf("Yellow State\r\n");
}

void Green_State(StateMachine_t * obj)
{    if( obj == NULL )
        return;

    printf("Green State\r\n");

    obj->current_State = Green_State;
    if( strcmp(obj->infoPtr,TERMINATION_STATE) == 0 )
    {
       obj->next_State = NULL; //Terminate this State Machine
    }
}

int main(void)
{
    while(SMPtr->next_State)
    {
        SMPtr->next_State(SMPtr);
    }
    return 0;
}
