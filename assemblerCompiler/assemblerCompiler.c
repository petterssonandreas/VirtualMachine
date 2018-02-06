#include <stdio.h>
#include "assemblerCompiler.h"
#include "../instruction.h"


struct OperationStringCodeType OperationStringCodes[NUM_DIFFERENT_OPERATIONS];

void compileCode(char* source_file);
void initOperationStringCodes();
unsigned int getOperationCode(char* op_str);


int main(int argc, char *argv[])
{
    printf("Source file: %s\n", argv[1]);
    initOperationStringCodes();
    compileCode(argv[1]);
}



void compileCode(char* source_file)
{
    FILE* file;
    file = fopen(source_file, "r");
    if(!file)
    {
        return;
    }

    char operation[MAX_INSTRUCTION_LENGTH];
    unsigned int op_code = 0;
    int data = 0;
    int destination_register_number = 0;
    int source_register_number = 0;

    while(!feof(file))
    {
        fscanf(file, "%s", &operation);
        printf("Compiling: %s\n", operation);

        op_code = getOperationCode(operation);
        
        printf("%s: %d\n", operation, op_code);

        switch(op_code)
        {
            case NOP:

                break;
            
            case PUS:

                break;

            case POP:

                break;

            case ADD:

                break;

            case SUB:

                break;

            case BRA:

                break;

            case BEQ:

                break;

            case BNE:

                break;

            case BGE:

                break;

            case BLE:

                break;

            case BRG:

                break;

            case BRL:

                break;

            case DUP:

                break;

            case PRINT_IM:
                // read chars until newline
                int c;
                do
                {
                    c = getc(file);
                } while(c != '\n');
                break;

            case PRINT_REG:

                break;

            case LOAD_IM:

                break;

            case MOVE_REGS:

                break;

            default:
                break;
            
        }

        //printf("|%c|\n", getc(file));


        /*if(getc(file) != ';')
        {
            break;
        }*/
    }

    fclose(file);
}


unsigned int getOperationCode(char* op_str)
{
    int i;
    int op_code = 0;
    for(i = 0; i < NUM_DIFFERENT_OPERATIONS; ++i)
    {
        if(!strcmp(op_str, OperationStringCodes[i].operation_string))
        {
            op_code = OperationStringCodes[i].operation_code;
            break;
        }
    }
    return op_code;
}


void initOperationStringCodes()
{
    strcpy(OperationStringCodes[0].operation_string, "NOP");
    OperationStringCodes[0].operation_code = NOP;
    strcpy(OperationStringCodes[1].operation_string, "PUS");
    OperationStringCodes[1].operation_code = PUS;
    strcpy(OperationStringCodes[2].operation_string, "POP");
    OperationStringCodes[2].operation_code = POP;
    strcpy(OperationStringCodes[3].operation_string, "ADD");
    OperationStringCodes[3].operation_code = ADD;
    strcpy(OperationStringCodes[4].operation_string, "BEQ");
    OperationStringCodes[4].operation_code = BEQ;
    strcpy(OperationStringCodes[5].operation_string, "BRA");
    OperationStringCodes[5].operation_code = BRA;
    strcpy(OperationStringCodes[6].operation_string, "PRINT_IM");
    OperationStringCodes[6].operation_code = PRINT_IM;
    strcpy(OperationStringCodes[7].operation_string, "DUP");
    OperationStringCodes[7].operation_code = DUP;
    strcpy(OperationStringCodes[8].operation_string, "LOAD_IM");
    OperationStringCodes[8].operation_code = LOAD_IM;
    strcpy(OperationStringCodes[9].operation_string, "MOVE_REGS");
    OperationStringCodes[9].operation_code = MOVE_REGS;
    strcpy(OperationStringCodes[10].operation_string, "PRINT_REG");
    OperationStringCodes[10].operation_code = PRINT_REG;
    strcpy(OperationStringCodes[11].operation_string, "SUB");
    OperationStringCodes[11].operation_code = SUB;
    strcpy(OperationStringCodes[12].operation_string, "BNE");
    OperationStringCodes[12].operation_code = BNE;
    strcpy(OperationStringCodes[13].operation_string, "BGE");
    OperationStringCodes[13].operation_code = BGE;
    strcpy(OperationStringCodes[14].operation_string, "BLE");
    OperationStringCodes[14].operation_code = BLE;
    strcpy(OperationStringCodes[15].operation_string, "BRG");
    OperationStringCodes[15].operation_code = BRG;
    strcpy(OperationStringCodes[16].operation_string, "BRL");
    OperationStringCodes[16].operation_code = BRL;
}






