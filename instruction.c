#include "instruction.h"

// *** All functions only used in assemblerCompiler ***
static struct MemoryType Memory;

void initMemory()
{
    Memory.number_of_instructions = 0;
}

int addInstruction(int operation, int data, int destination_reg_number, 
    int source_reg_number, int store_size_bytes)
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
        instr_p->destination_reg_number = destination_reg_number;
        instr_p->source_reg_number = source_reg_number;
        instr_p->store_size_bytes = store_size_bytes;

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
        return unknown_instr;
    }
}

int getNumberOfInstructions()
{
    return Memory.number_of_instructions;
}
