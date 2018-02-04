#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "instruction.h"
#include "register.h"

#define FILE_DOESENT_EXIST 1
#define FILE_READ_OK 2




int readInstructions()
{
    FILE* fp;
    fp = fopen("compiled_code.txt", "r");
    if(!fp)
    {
        return FILE_DOESENT_EXIST;
    }

    int op_code;
    int data;
    int dest_reg_num;
    int source_reg_num;

    while(!feof(fp))
    {
        fscanf(fp, "%d,%d,%d,%d", &op_code, &data, &dest_reg_num, &source_reg_num);
        printf("Adding instruction: op=%d, data=%d\n", op_code, data);
        addInstruction(op_code, data, dest_reg_num, source_reg_num);

        if(getc(fp) != ';')
        {
            break;
        }
    }

    fclose(fp);

    return FILE_READ_OK;
}



void runCode()
{
    int pc = 0;
    int temp;

    struct InstructionType instr;

    while(pc < MAX_NUM_INSTRUCTIONS)
    {
        instr = getInstruction(pc);
        switch(instr.operation)
        {
            case NOP:
                printf("Running code NOP\n");
                pc++;
                break;

            case PUS:
                printf("Running code PUS,%d\n", instr.data);
                push(instr.data);
                pc++;
                break;

            case POP:
                //TODO
                break;

            case ADD:
                // dest = dest + source
                printf("Running code ADD R%d,R%d\n", instr.destination_reg_number, instr.source_reg_number);
                int sum = 0;
                readRegister(instr.destination_reg_number, &temp);
                sum += temp;
                readRegister(instr.source_reg_number, &temp);
                sum += temp;
                writeRegister(instr.destination_reg_number, sum);
                pc++;
                break;

            case BEQ:
                //TODO
                break;

            case BRA:
                printf("Running code BRA,%d\n", instr.data);
                pc = instr.data;
                break;

            case PRINT_IM:
                printf("Running code PRI,%d\n", instr.data);
                printf("%d\n", instr.data);
                pc++;
                break;

            case DUP:
                //TODO
                break;
            
            case LOAD_IM:
                // Load a value (immediate) in a register
                printf("Running code LOAD_IM,%d, to R%d\n", instr.data, instr.destination_reg_number);
                writeRegister(instr.destination_reg_number, instr.data);
                pc++;
                break;

            case MOVE_REGS:
                // Copy the value in one reg to another
                printf("Running code MOVE_REGS, dest: %d, source: %d\n", instr.destination_reg_number, instr.source_reg_number);
                readRegister(instr.source_reg_number, &temp);
                writeRegister(instr.destination_reg_number, temp);
                break;

            case PRINT_REG:
                // Print the value stored in the source register
                printf("Running code PRINT_REG,%d\n", instr.source_reg_number);
                readRegister(instr.source_reg_number, &temp);
                printf("R%d: %d\n", instr.source_reg_number, temp);
                pc++;
                break;

            default:
                printf("Unknown instruction: %d,%d,%d,%d\n", instr.operation, instr.data, instr.destination_reg_number, instr.source_reg_number);
                return;
                break;
        }
    }
}



int main(int argc, char *argv[])
{
    initMemory();
    initStack();
    initRegs();

    if(readInstructions() != FILE_READ_OK)
    {
        return 0;
    }

    runCode();
}
