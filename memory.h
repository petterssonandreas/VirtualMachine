#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>


#define MEMORY_SIZE_BYTES 32

// Data sizes
// 
// Operation: 1 byte
// Register numbers: 1 byte
// Addresses: 4 bytes
// Immediates: 4 bytes

struct ByteMemoryType
{
    uint8_t mem[MEMORY_SIZE_BYTES]; 
};

// If all present, will be in order: OP, destR, sourceR, Im/Address
// If not applicable, remove and move the others together


void storeOperation(int address, int operation_code);
void storeRegisterNumber(int address, int register_number);
void storeAddress(int address, int address_to_store);
void storeImmediate(int address, int immediate);

int getOperation(int address);
int getRegisterNumber(int address);
int getStoredAddress(int address);
int getImmediate(int address);

void printMemory();

#endif