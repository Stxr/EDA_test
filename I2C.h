#ifndef __I2C_H_
#define __I2C_H_
#include <reg51.h>
#include "delay.h"
void I2C_start(void);
void I2C_start(void);
char I2C_sendbyte(char dat);
char I2C_readbyte(void);
#endif
