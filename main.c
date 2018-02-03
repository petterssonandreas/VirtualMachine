#include<stdio.h>

#include "stack.h"
#include "instruction.h"

#define FILE_DOESENT_EXIST 1
#define FILE_READ_OK 2




int readInstructions()
{
    FILE* fp;
    fp = fopen("compiled_code.txt");
    if(!fp)
    {
        return FILE_DOESENT_EXIST;
    }

    int c;
    int op_code;
    int data;
    int reading_op = 1;
    int reached_end = 0;
    while(((c = getc(fp)) != EOF) && !reached_end)
    {
        switch(c)
        {
            case ',' :
                reading_op = !reading_op;
                break;
            
            case ';' :
                reading_op = !reading_op;
                addInstruction(op_code, data);
                break;
            
            case '#' :
                reached_end = 1;
                break;

            default:
                if(reading_op)
                {
                    op_code = c;
                }
                else
                {
                    data = c;
                }
                break;
        }
    }
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
            case PRI:
                printf("Running code PRI,%d\n", instr.data);
                printf("%d\n", instr.data);
                pc++;
                break;

            case BRA:
                printf("Running code BRA,%d\n", instr.data);
                pc = instr.data;
                break;

            default:
                printf("Unknown instruction\n");
                break;
        }
    }
}



int main(int argc, char *argv[])
{
    initMemory();
    initStack();

    if(readInstructions() != FILE_READ_OK)
    {
        return 0;
    }

    runCode();
}


