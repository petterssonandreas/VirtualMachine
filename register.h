#ifndef REGISTER_H
#define REGISTER_H

#define NUMBER_OF_REGS 5

#define REG_OK 1
#define REG_NUM_UNKNOWN 2


void initRegs();

int writeRegister(int reg_number, int data);
int readRegister(int reg_number, int* read_data);

#endif
