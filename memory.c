#include <stdint.h>
#include "memory.h"

struct MemoryType Memory;

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
    int* memory_location = &Memory.mem[address];
    *memory_location = address_to_store;
}

void storeImmediate(int address, int immediate)
{
    // 4 bytes
    int* memory_location = &Memory.mem[address];
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
    int* storedAddress_p = &Memory.mem[address];
    return *storedAddress_p;
}


int getImmediate(int address)
{
    // 4 bytes long
    int* immediate_p = &Memory.mem[address];
    return *immediate_p;
}
