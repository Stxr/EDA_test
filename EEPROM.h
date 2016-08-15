#ifndef __EEPROM_H_
#define __EEPROM_H_
#include <reg51.h>
#include "delay.h"
#include "I2C.h"
void AT24C02_write(char addr,char dat);
char AT24C02_read(char addr);
#endif
