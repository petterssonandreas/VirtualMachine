#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 1024

#define PUSH_OK 1
#define PUSH_STACK_FULL 2

#define POP_OK 1
#define POP_STACK_EMPTY 2


struct StackType
{
    // Stack holding ints
    int stack[MAX_STACK_SIZE];
    int top;
};

struct StackType Stack;

void initStack();

int push(int data);
int pop(int* popped_data);


#endif