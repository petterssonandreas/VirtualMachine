#include <stdio.h>
#include <string.h>
#include "assemblerCompiler.h"
#include "../instruction.h"


struct OperationStringCodeType OperationStringCodes[NUM_DIFFERENT_OPERATIONS];
static struct StringKeyIntValueLookupType Labels;

void compileCode(char* source_file);
void initOperationStringCodes();
unsigned int getOperationCode(char* op_str);
void clearLine(FILE* file);
void writeCode(char* filename);
int calculateByteAddress(int instruction_number);
void addLabel(char* label_string, int byte_address);


int main(int argc, char *argv[])
{
    printf("Source file: %s\n", argv[1]);
    initOperationStringCodes();
    initMemory();
    if(argc >= 2)
    {
        compileCode(argv[1]);
        writeCode("..\\a.out");
    }
}



void writeCode(char* filename)
{
    printf("Starting write\n");

    FILE* file;
    file = fopen(filename, "w");
    if(!file)
    {
        return;
    }

    printf("Created file ok\n");

    int i;
    for(i = 0; i < getNumberOfInstructions(); ++i)
    {
        struct InstructionType instruction = getInstruction(i);
        fprintf(file, "%d,%d,%d,%d;", instruction.operation, 
                instruction.destination_reg_number, 
                instruction.source_reg_number,
                instruction.data);
    }

    fclose(file);
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
    int destination_reg_number = 0;
    int source_reg_number = 0;
    int store_size_bytes;

    char register_and_data_string[MAX_ARGUMENTS_LENGTH];

    while(!feof(file))
    {
        data = 0;
        destination_reg_number = 0;
        source_reg_number = 0;

        fscanf(file, "%s", &operation);
        printf("Compiling: %s\n", operation);

        op_code = getOperationCode(operation);
        
        printf("%s: %d\n", operation, op_code);

        switch(op_code)
        {
            case NOP:
                store_size_bytes = 1;
                clearLine(file);
                break;
            
            case PUS:
                // TODO
                break;

            case POP:
                // TODO
                break;

            case ADD:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d,R%d", &destination_reg_number, &source_reg_number);
                printf("Compiling: %s R%d,R%d\n", operation, destination_reg_number, source_reg_number);
                store_size_bytes = 3;
                clearLine(file);
                break;

            case SUB:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d,R%d", &destination_reg_number, &source_reg_number);
                printf("Compiling: %s R%d,R%d\n", operation, destination_reg_number, source_reg_number);
                store_size_bytes = 3;
                clearLine(file);
                break;

            case BRA:
                fscanf(file, "%d", &data);
                data = calculateByteAddress(data);
                printf("Compiling: %s %d\n", operation, data);
                store_size_bytes = 5;
                clearLine(file);
                break;

            case BEQ:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d,R%d,%d", 
                       &destination_reg_number, &source_reg_number, &data);
                data = calculateByteAddress(data);
                printf("Compiling: %s %d\n", operation, data);
                store_size_bytes = 7;
                clearLine(file);
                break;

            case BNE:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d,R%d,%d", 
                       &destination_reg_number, &source_reg_number, &data);
                data = calculateByteAddress(data);
                printf("Compiling: %s %d\n", operation, data);
                store_size_bytes = 7;
                clearLine(file);
                break;

            case BGE:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d,R%d,%d", 
                       &destination_reg_number, &source_reg_number, &data);
                data = calculateByteAddress(data);
                printf("Compiling: %s %d\n", operation, data);
                store_size_bytes = 7;
                clearLine(file);
                break;

            case BLE:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d,R%d,%d", 
                       &destination_reg_number, &source_reg_number, &data);
                data = calculateByteAddress(data);
                printf("Compiling: %s %d\n", operation, data);
                store_size_bytes = 7;
                clearLine(file);
                break;

            case BRG:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d,R%d,%d", 
                       &destination_reg_number, &source_reg_number, &data);
                data = calculateByteAddress(data);
                printf("Compiling: %s %d\n", operation, data);
                store_size_bytes = 7;
                clearLine(file);
                break;

            case BRL:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d,R%d,%d", 
                       &destination_reg_number, &source_reg_number, &data);
                data = calculateByteAddress(data);
                printf("Compiling: %s %d\n", operation, data);
                store_size_bytes = 7;
                clearLine(file);
                break;

            case DUP:
                // TODO
                break;

            case PRINT_IM:
                fscanf(file, "%d", &data);
                printf("Compiling: %s %d\n", operation, data);
                store_size_bytes = 5;
                clearLine(file);
                break;

            case PRINT_REG:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d", &source_reg_number);
                printf("Compiling: %s R%d\n", operation, source_reg_number);
                store_size_bytes = 2;
                clearLine(file);
                break;

            case LOAD_IM:
                fscanf(file, "%d", &data);
                printf("Compiling: %s %d\n", operation, data);
                store_size_bytes = 6;
                clearLine(file);
                break;

            case MOVE_REGS:
                fscanf(file, "%s", &register_and_data_string);
                sscanf(register_and_data_string, "R%d,R%d", &destination_reg_number, &source_reg_number);
                printf("Compiling: %s R%d,R%d\n", operation, destination_reg_number, source_reg_number);
                store_size_bytes = 3;
                clearLine(file);
                break;

            default:
                // Check if label, i.e. if colon at end
                printf("%d: %c\n", strlen(operation), operation[strlen(operation)-1]);
                if(operation[strlen(operation)-1] == ':')
                {
                    printf("SHOULD BE LABEL\n");
                    char label[MAX_INSTRUCTION_LENGTH];
                    strncpy(label, operation, strlen(operation)-1);
                    printf("Label: %s\n", label);
                    int byte_address = calculateByteAddress(getNumberOfInstructions());
                    addLabel(label, byte_address);
                }

                printf("Unknown instruction, setting to NOP\n");
                op_code = NOP;
                store_size_bytes = 1;
                clearLine(file);
                break;
            
        }

        // Gotten all data, add instruction
        addInstruction(op_code, data, destination_reg_number, source_reg_number, 
                       store_size_bytes);
    }

    fclose(file);
}

void clearLine(FILE* file)
{
    // Read chars until newline or EOF
    int c;
    do
    {
        c = getc(file);
    } while(c != '\n' && c != EOF);
}

int calculateByteAddress(int instruction_number)
{
    int byte_number = 0;

    struct InstructionType instr;

    for(int i = 0; i < instruction_number; ++i)
    {
        instr = getInstruction(i);
        byte_number += instr.store_size_bytes;
    }

    return byte_number;
}


void addLabel(char* label_string, int byte_address)
{
    // Assumes label not already present
    strncpy(Labels.dictionary[Labels.number_of_entries].key, label_string, strlen(label_string));
    Labels.dictionary[Labels.number_of_entries].value = byte_address;
    Labels.number_of_entries++;
}


unsigned int getOperationCode(char* op_str)
{
    int i;
    int op_code = UNKNOWN_INSTRUCTION;
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






