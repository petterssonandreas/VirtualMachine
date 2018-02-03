#include "stack.h"


void initStack()
{
    Stack.top = 0;
}


int push(int data)
{
    if(Stack.top >= MAX_STACK_SIZE)
    {
        // Stack full, discard
        return PUSH_STACK_FULL;
    }
    else
    {
        // Stack not full
        Stack.stack[Stack.top] = data;
        Stack.top++;
        return PUSH_OK;
    }
}


int pop(int* popped_data)
{
    if(Stack.top > 0)
    {
        // Stack not empty
        Stack.top--;
        *popped_data = Stack.stack[Stack.top];
        return POP_OK;
    }
    else
    {
        // Stack empty, nothing to pop
        return POP_STACK_EMPTY;
    }
}
