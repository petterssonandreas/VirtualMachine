#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define NOP 0
#define PUS 1
#define POP 2
#define ADD 3
#define BEQ 4
#define BRA 5
#define PRI 6
#define DUP 7

#define unknown_address 128

#define MEM_FULL 1
#define INSTRUCTION_ADDED 2

#define MAX_NUM_INSTRUCTIONS 1024

struct InstructionType
{
    int operation;
    int data;
};

struct MemoryType
{
    struct InstructionType memory[MAX_NUM_INSTRUCTIONS];
    int number_of_instructions;
};


void initMemory();

int addInstruction(int operation, int data);
struct InstructionType getInstruction(int address);

#endif
