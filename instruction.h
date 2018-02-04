#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define NOP 0
#define PUS 1
#define POP 2
#define ADD 3
#define BEQ 4
#define BRA 5
#define PRINT_IM 6
#define DUP 7
#define LOAD_IM 8
#define MOVE_REGS 9
#define PRINT_REG 10
#define SUB 11
#define BNE 12
#define BGE 13 // branch on greater or equal 0
#define BLE 14 // branch on less or equal 0
#define BRG 15 // branch on greater than 0
#define BRL 16 // branch on less than 0

#define unknown_address 128

#define MEM_FULL 1
#define INSTRUCTION_ADDED 2

#define MAX_NUM_INSTRUCTIONS 1024

struct InstructionType
{
    int operation;
    int data;
    int destination_reg_number;
    int source_reg_number;
};

struct MemoryType
{
    struct InstructionType memory[MAX_NUM_INSTRUCTIONS];
    int number_of_instructions;
};


void initMemory();

int addInstruction(int operation, int data, int destination_reg_number, int source_reg_number);
struct InstructionType getInstruction(int address);

#endif
