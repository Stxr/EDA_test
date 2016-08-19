#ifndef __EEPROM_H_
#define __EEPROM_H_
#include <reg51.h>
#include "delay.h"
#include "I2C.h"
void AT24C02_write(char addr,char dat);
char AT24C02_read(char addr);
void AT24C02_writestring(char *s);//写入一个数组，从地址0开始储存
#endif
