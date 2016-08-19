#include "EEPROM.h"
void AT24C02_write(char addr,char dat)
{
  I2C_start();
  I2C_sendbyte(0xa0);//发送写命令
  I2C_sendbyte(addr);
  I2C_sendbyte(dat);
  I2C_end();
  Delay_5ms();
}
char AT24C02_read(char addr)
{
  char dat;
  I2C_start();
  I2C_sendbyte(0xA0);//发送写命令
  I2C_sendbyte(addr);
  I2C_start();
  I2C_sendbyte(0xA1);
  dat=I2C_readbyte();
  I2C_end();
  return dat;
}
void AT24C02_writestring(char *s)
{
  char i;
  for(i=0;s[1]!='\0';i++)
  {
    AT24C02_write(i,s[i]);
  }
}
