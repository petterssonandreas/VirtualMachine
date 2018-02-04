#include "register.h"

static int Registers[NUMBER_OF_REGS];


void initRegs()
{
    int i;
    for(i = 0; i < NUMBER_OF_REGS; ++i)
    {
        Registers[i] = 0;
    }
}


int writeRegister(int reg_number, int data)
{
    if(reg_number < NUMBER_OF_REGS)
    {
        Registers[reg_number] = data;
        return REG_OK;
    }
    else
    {
        return REG_NUM_UNKNOWN;
    }
}


int readRegister(int reg_number, int* read_data)
{
    if(reg_number < NUMBER_OF_REGS)
    {
        *read_data = Registers[reg_number];
        return REG_OK;
    }
    else
    {
        return REG_NUM_UNKNOWN;
    }
}
