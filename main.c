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

    while(!feof(fp))
    {
        fscanf(fp, "%d,%d", &op_code, &data);
        printf("Adding instruction: op=%d, data=%d\n", op_code, data);
        addInstruction(op_code, data);

        if(getc(fp) != ';')
        {
            break;
        }
    }

    return FILE_READ_OK;
}



void runCode()
{
    int pc = 0;

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
                //TODO
                break;

            case BEQ:
                //TODO
                break;

            case BRA:
                printf("Running code BRA,%d\n", instr.data);
                pc = instr.data;
                break;

            case PRI:
                printf("Running code PRI,%d\n", instr.data);
                printf("%d\n", instr.data);
                pc++;
                break;

            case DUP:
                printf("Running code BRA,%d\n", instr.data);
                pc = instr.data;
                break;

            default:
                printf("Unknown instruction\n");
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
