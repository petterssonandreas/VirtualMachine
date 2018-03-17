#include <stdint.h>
#include <stdio.h>
#include "memory.h"

static struct ByteMemoryType Memory;

// ALWAYS ASSUMES ADDRESS WITHIN BOUNDS !!!


void storeOperation(int address, int operation_code)
{
    Memory.mem[address] = operation_code;
}

void storeRegisterNumber(int address, int register_number)
{
    Memory.mem[address] = register_number;
}

void storeAddress(int address, int address_to_store)
{
    // 4 bytes
    int* memory_location = (int*) &Memory.mem[address];
    *memory_location = address_to_store;
}

void storeImmediate(int address, int immediate)
{
    // 4 bytes
    int* memory_location = (int*) &Memory.mem[address];
    *memory_location = immediate;
}



int getOperation(int address)
{
    return (int) Memory.mem[address];
}


int getRegisterNumber(int address)
{
    return (int) Memory.mem[address];
}


int getStoredAddress(int address)
{
    // 4 bytes long
    int* storedAddress_p = (int*) &Memory.mem[address];
    return *storedAddress_p;
}


int getImmediate(int address)
{
    // 4 bytes long
    int* immediate_p = (int*) &Memory.mem[address];
    return *immediate_p;
}



void printMemory()
{
    printf("\n\n MEMORY CONTENTS \n\n");

    for(int i = 0; i < MEMORY_SIZE_BYTES; ++i)
    {
        printf("%d:  %d\n", i, Memory.mem[i]);
    }
    printf("\n");
}