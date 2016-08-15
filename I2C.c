#include "I2C.h"
sbit I2C_SDA=P2^0;
sbit I2C_SCL=P2^1;
void I2C_start(void)
{
  I2C_SDA=1;
  Delay_10us();
  I2C_SCL=1;
  Delay_10us();
  I2C_SDA=0;
  Delay_10us();
  I2C_SCL=0;
  Delay_10us();
}
void I2C_end(void)
{
  I2C_SDA=0;
  Delay_10us();
  I2C_SCL=1;
  Delay_10us();
  I2C_SDA=1;
  Delay_10us();
}
char I2C_sendbyte(char dat)
{
  char i=0,t;
  I2C_SCL=0;
  for(i=0;i<8;i++)
  {
    I2C_SDA=dat>>7;
    dat<<=1;
    Delay_10us();
    I2C_SCL=1;
    Delay_10us();
    I2C_SCL=0;
    Delay_10us();
  }
  I2C_SDA=1;
  Delay_10us();
  I2C_SCL=1;
  while (I2C_SDA)
  {
    t++;
    if(t>200)
    {
      I2C_SCL=0;
      Delay_10us();
      return 0;
    }
  }
  I2C_SCL=0;
  Delay_10us();
	return 1;
}
char I2C_readbyte(void)
{
  char i=0,dat=0;
  I2C_SDA=1;
  for(i=0;i<8;i++)
  {
    I2C_SCL=1;
    Delay_10us();
    dat<<=1;
    dat|=I2C_SDA;
    Delay_10us();
    I2C_SCL=0;
    Delay_10us();
  }
  return dat;
}
