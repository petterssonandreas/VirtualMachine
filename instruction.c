#include "instruction.h"

void initMemory()
{
    Memory.number_of_instructions = 0;
}


int addInstruction(int operation, int data)
{
    if(Memory.number_of_instructions >= MAX_NUM_INSTRUCTIONS)
    {
        // Memory full, discard
        return MEM_FULL;
    }
    else
    {
        struct InstructionType* instr_p = &Memory.memory[Memory.number_of_instructions];
        instr_p->operation = operation;
        instr_p->data = data;

        Memory.number_of_instructions++;
        return INSTRUCTION_ADDED;
    }
}

struct InstructionType getInstruction(int address)
{
    if(address < MAX_NUM_INSTRUCTIONS)
    {
        return Memory.memory[address];
    }
    else
    {
        struct InstructionType unknown_instr;
        unknown_instr.operation = unknown_address;
        unknown_instr.data = unknown_address;
        return unknown_instr;
    }
}
