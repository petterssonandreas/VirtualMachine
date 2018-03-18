#ifndef ASSEMBLERCOMPILER_H
#define ASSEMBLERCOMPILER_H

#define MAX_INSTRUCTION_LENGTH 100
#define NUM_DIFFERENT_OPERATIONS 17
#define MAX_ARGUMENTS_LENGTH 100

#define MAX_NUM_LABELS 100

struct OperationStringCodeType
{
    char operation_string[MAX_INSTRUCTION_LENGTH];
    unsigned int operation_code;
};

struct StringKeyIntValueType
{
    char key[MAX_INSTRUCTION_LENGTH];
    int value;
};

struct StringKeyIntValueLookupType
{
    struct StringKeyIntValueType dictionary[MAX_NUM_LABELS];
    unsigned int number_of_entries;
};

#endif