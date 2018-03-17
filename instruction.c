#include "instruction.h"

// *** Not used anymore ***
static struct MemoryType Memory;

// *** Not used anymore ***
void initMemory()
{
    Memory.number_of_instructions = 0;
}

// *** Not used anymore ***
int addInstruction(int operation, int data, int destination_reg_number, int source_reg_number)
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

        Memory.number_of_instructions++;
        return INSTRUCTION_ADDED;
    }
}

// *** Not used anymore ***
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

// *** Not used anymore ***
int getNumberOfInstructions()
{
    return Memory.number_of_instructions;
}
