#ifndef ASSEMBLERCOMPILER_H
#define ASSEMBLERCOMPILER_H

#define MAX_INSTRUCTION_LENGTH 10
#define NUM_DIFFERENT_OPERATIONS 17
#define MAX_ARGUMENTS_LENGTH 100

struct OperationStringCodeType
{
    char operation_string[MAX_INSTRUCTION_LENGTH];
    unsigned int operation_code;
};

#endif