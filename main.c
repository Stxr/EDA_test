#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
// #include "keydown.h" //键盘
#include "digital_control.h"//数码管
#include "I2C.h"
#include "EEPROM.h"
#define GPIO_KEY P1
sbit led=P2^7;
char Keydown(void);
void Interrupt_Init(void);
void TIM_Init(void);
void Usart_Init(void);
char flag=0;
char test[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char flag_key;
int timer=0;
char keyvalue;
int main(void)
{
  // char num;
  // Usart_Init();
  // TIM_Init();
  // Interrupt_Init();
  // LCD1602_Init();// LCD初始化
  // AT24C02_write(2,3);
  // LCD1602_Writedata('A');
  // num=AT24C02_read(2);
  // LCD1602_Writedata(num+'0');
  while(1)
  {

  //  led=flag;
  }
}

char Keydown(void)//按键
{
  GPIO_KEY=0X0F;
  if(GPIO_KEY!=0X0F)
  {
    Delay_5ms();
    if(GPIO_KEY!=0X0F)
    {
      flag_key=1;
      GPIO_KEY=0X0F;
      switch (GPIO_KEY)
       {
        case 0X07: keyvalue=0;  break;
        case 0x0B: keyvalue=1;  break;
        case 0x0D: keyvalue=2;  break;
        case 0x0E: keyvalue=3;  break;
      }
      GPIO_KEY=0XF0;
      switch (GPIO_KEY)
      {
        case 0X70: keyvalue+=0;  break;
        case 0xB0: keyvalue+=4;  break;
        case 0xD0: keyvalue+=8;  break;
        case 0xE0: keyvalue+=12; break;
      }
      while(GPIO_KEY!=0XF0);
    }
  }
  return keyvalue;
}
void Interrupt_Init(void)
{
  EA=1;
  EX0=1;
  IT0=1;//下降沿触发

  EX1=1;
  IT1=1;
}
void TIM_Init(void)
{
  EA=1;
  TMOD=0x01;//工作方式1
  TH0=(65536-1000)/256;
  TL0=(65536-1000)%256;
  ET0=1;//打开定时器中断
  TR0=1;//打开定时器0
}
void It0(void) interrupt 0
{
  EX0=0;
  LCD1602_Writecom(0X01);
  flag=~flag;
  EX0=1;
}
void It1(void) interrupt 2
{
  EX1=0;
  flag=1;
  EX1=1;
}
void TIMER0 (void) interrupt 1
{
  TH0=(65536-1000)/256;
  TL0=(65536-1000)%256;
  timer++;
  if(timer==1000)
  {
    P2=~P2;
    timer=0;
  }
}
void Usart_Init(void)
{
  EA=1;
  ES=1;
  TR1=1;
  TMOD=0X20;
  SCON=0X50;
  TH1=0XFD;
  TL1=0XFD;
}
void Usart_interrput(void) interrupt 4
{
  char buff;
  if(RI)
  {
    RI=0;
    buff=SBUF;
    SBUF=buff;
  }
  else
    TI=0;
}
