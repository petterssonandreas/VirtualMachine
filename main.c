#include <stdio.h>
#include <stdlib.h>
//#include "stack.h"
#include "instruction.h"
#include "register.h"
#include "memory.h"

#define FILE_UNDEFINED 1
#define FILE_READ_OK 2
#define FILE_CODE_TOO_LONG 3


int addByteInstruction(int instructionAddress, int op_code, int immediate,
    int dest_reg_num, int source_reg_num)
{
    storeOperation(instructionAddress, op_code);
    ++instructionAddress;

    // Figure out what to store more
    switch(op_code)
    {
        case NOP:
            // Don't store anything
            break;

        case ADD:
        case SUB:
            // dest = dest +/- source
            // Store reg number for dest and source
            storeRegisterNumber(instructionAddress, dest_reg_num);
            ++instructionAddress;
            storeRegisterNumber(instructionAddress, source_reg_num);
            ++instructionAddress;
            break;

        case LOAD_IM:
            // Store reg number for dest and immediate value
            storeRegisterNumber(instructionAddress, dest_reg_num);
            ++instructionAddress;
            storeImmediate(instructionAddress, immediate);
            instructionAddress += 4;
            break;

        case MOVE_REGS:
            // dest = source
            // Store reg number for dest and source
            storeRegisterNumber(instructionAddress, dest_reg_num);
            ++instructionAddress;
            storeRegisterNumber(instructionAddress, source_reg_num);
            ++instructionAddress;
            break;

        case PRINT_REG:
            // Store reg number for source
            storeRegisterNumber(instructionAddress, source_reg_num);
            ++instructionAddress;
            break;

        case PRINT_IM:
            // Store immediate
            storeImmediate(instructionAddress, immediate);
            instructionAddress += 4;
            break;

        case BRA:
            // Store address
            storeAddress(instructionAddress, immediate);
            instructionAddress += 4;
            break;

        case BEQ:
        case BNE:
        case BGE:
        case BLE:
        case BRG:
        case BRL:
            // Store reg number for dest and source
            storeRegisterNumber(instructionAddress, dest_reg_num);
            ++instructionAddress;
            storeRegisterNumber(instructionAddress, source_reg_num);
            ++instructionAddress;
            storeAddress(instructionAddress, immediate);
            instructionAddress += 4;
            break;

        default:
            // Unknown instruction
            break;
    }

    return instructionAddress;
}







int readInstructions()
{
    FILE* fp;
    fp = fopen("a.out", "r");
    if(!fp)
    {
        return FILE_UNDEFINED;
    }

    int op_code;
    int data;
    int dest_reg_num;
    int source_reg_num;

    int instructionAddress = 0;

    while(!feof(fp))
    {
        if(fscanf(fp, "%d,%d,%d,%d", &op_code, &dest_reg_num, &source_reg_num, &data) <= 0)
        {
            break;
        }
        printf("Adding instruction: op=%d, data=%d\n", op_code, data);
        instructionAddress = addByteInstruction(instructionAddress, op_code, data, dest_reg_num, source_reg_num);

        if(getc(fp) != ';')
        {
            break;
        }

        if(instructionAddress > MEMORY_SIZE_BYTES - 8)
        {
            fclose(fp);
            return FILE_CODE_TOO_LONG;
        }
    }

    fclose(fp);

    return FILE_READ_OK;
}

int subTwoRegs(int destination_reg_number, int source_reg_number)
{
    int temp;
    int diff = 0;
    readRegister(destination_reg_number, &temp);
    diff += temp;
    readRegister(source_reg_number, &temp);
    diff -= temp;

    return diff;
}




void runCode()
{
    int pc = 0;
    int temp;

    struct InstructionType instr;

    while(pc < MAX_NUM_INSTRUCTIONS)
    {
        instr.operation = getOperation(pc);
        ++pc;

        switch(instr.operation)
        {
            case NOP:
                printf("Running code NOP\n");
                break;
            
            /*
            case PUS:
                printf("Running code PUS,%d\n", instr.data);
                push(instr.data);
                pc++;
                break;

            case POP:
                //TODO
                break;
            */

            case ADD:
                // dest = dest + source
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;

                printf("Running code ADD R%d,R%d\n", instr.destination_reg_number, instr.source_reg_number);
                int sum = 0;
                readRegister(instr.destination_reg_number, &temp);
                sum += temp;
                readRegister(instr.source_reg_number, &temp);
                sum += temp;
                writeRegister(instr.destination_reg_number, sum);
                break;

            case SUB:
                // dest = dest - source
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;
                
                printf("Running code SUB R%d,R%d\n", instr.destination_reg_number, instr.source_reg_number);
                int diff = subTwoRegs(instr.destination_reg_number, instr.source_reg_number);
                writeRegister(instr.destination_reg_number, diff);
                break;

            case BEQ:
                // Branch if two regs are the same, i.e. SUB produces 0
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.data = getStoredAddress(pc);
                pc += 4;

                printf("Running code BEQ R%d,R%d,%d\n", instr.destination_reg_number, instr.source_reg_number, instr.data);
                if(subTwoRegs(instr.destination_reg_number, instr.source_reg_number) == 0)
                {
                    pc = instr.data;
                }
                break;

            case BNE:
                // Branch if two regs are NOT the same
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.data = getStoredAddress(pc);
                pc += 4;

                printf("Running code BNE R%d,R%d,%d\n", instr.destination_reg_number, instr.source_reg_number, instr.data);
                if(subTwoRegs(instr.destination_reg_number, instr.source_reg_number) != 0)
                {
                    pc = instr.data;
                }
                break;

            case BGE:
                // branch on greater or equal 0
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.data = getStoredAddress(pc);
                pc += 4;

                printf("Running code BGE R%d,R%d,%d\n", instr.destination_reg_number, instr.source_reg_number, instr.data);
                if(subTwoRegs(instr.destination_reg_number, instr.source_reg_number) >= 0)
                {
                    pc = instr.data;
                }
                break;

            case BLE:
                // branch on less or equal 0
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.data = getStoredAddress(pc);
                pc += 4;

                printf("Running code BGE R%d,R%d,%d\n", instr.destination_reg_number, instr.source_reg_number, instr.data);
                if(subTwoRegs(instr.destination_reg_number, instr.source_reg_number) <= 0)
                {
                    pc = instr.data;
                }
                break;

            case BRG:
                // branch on greater than 0
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.data = getStoredAddress(pc);
                pc += 4;

                printf("Running code BGE R%d,R%d,%d\n", instr.destination_reg_number, instr.source_reg_number, instr.data);
                if(subTwoRegs(instr.destination_reg_number, instr.source_reg_number) > 0)
                {
                    pc = instr.data;
                }
                break;

            case BRL:
                // branch on greater than 0
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.data = getStoredAddress(pc);
                pc += 4;

                printf("Running code BGE R%d,R%d,%d\n", instr.destination_reg_number, instr.source_reg_number, instr.data);
                if(subTwoRegs(instr.destination_reg_number, instr.source_reg_number) < 0)
                {
                    pc = instr.data;
                }
                break;

            case BRA:
                instr.data = getStoredAddress(pc);
                pc += 4;
                
                printf("Running code BRA,%d\n", instr.data);
                pc = instr.data;
                break;

            case PRINT_IM:
                instr.data = getStoredAddress(pc);
                pc += 4;

                printf("Running code PRI %d\n", instr.data);
                printf("%d\n", instr.data);
                break;

            /*
            case DUP:
                //TODO
                break;
            */
            
            case LOAD_IM:
                // Load a value (immediate) in a register
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.data = getImmediate(pc);
                pc += 4;

                printf("Running code LOAD_IM,%d, to R%d\n", instr.data, instr.destination_reg_number);
                writeRegister(instr.destination_reg_number, instr.data);
                break;

            case MOVE_REGS:
                // Copy the value in one reg to another
                instr.destination_reg_number = getRegisterNumber(pc);
                ++pc;
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;

                printf("Running code MOVE_REGS, dest: %d, source: %d\n", instr.destination_reg_number, instr.source_reg_number);
                readRegister(instr.source_reg_number, &temp);
                writeRegister(instr.destination_reg_number, temp);
                break;

            case PRINT_REG:
                // Print the value stored in the source register
                instr.source_reg_number = getRegisterNumber(pc);
                ++pc;

                printf("Running code PRINT_REG,%d\n", instr.source_reg_number);
                readRegister(instr.source_reg_number, &temp);
                printf("R%d: %d\n", instr.source_reg_number, temp);
                break;

            default:
                printf("Unknown instruction operation code: %d\n", instr.operation);
                return;
                break;
        }
    }
}



int main(int argc, char *argv[])
{
    initRegs();

    if(readInstructions() != FILE_READ_OK)
    {
        return 0;
    }

    printMemory();
    runCode();
}
