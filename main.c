#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "I2C.h"
#include "EEPROM.h"
#include "NRF2401.h"
#define GPIO_KEY P1
#define DIG_GPIO_DUAN P0
#define DIG_GPIO_WEI P2


sbit NRF_IR  = P2^2;
//char Keydown(void);
//void Interrupt_Init(void);
//void TIM_Init(void);
//void Usart_Init(void);
//void Display_digital(void);
//void Usart_pro(void);

//char flag=0;
unsigned char rece_buf[32];
unsigned char code DIG_PLACE[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//位选控制   查表的方法控制
unsigned char code DIG_CODE[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};  //0~F的显示码
//char uart_buff[32],uart_i=0;
//char test[32]=0;
//char flag_key;
//int timer=0;
//char keyvalue;

int main(void)
{
//  int i=0,a;
//  char num;
  // Usart_Init();
  // TIM_Init();
  // Interrupt_Init();
  LCD1602_Init();// LCD初始化
  // LCD1602_Writedata('G');
	// while(NRF24L01_Check()); // 等待检测到NRF24L01，程序才会向下执行
  NRF24L01_RT_Init();
  LCD1602_Writedata('A');
  while(1)
  {
  //	if(NRF_IR==0)	 	// 如果无线模块接收到数据
  	{
  		if(NRF24L01_RxPacket(rece_buf)==0)
  		{
        // LCD1602_Writedata('A');
  			Sendlength(rece_buf);
  		}
  	}
   // Keydown();
//    if(keyvalue!=15)
//    {
//      AT24C02_write(2,keyvalue);
//    }

//    num=AT24C02_read(2);
//    LCD1602_Writedata(num+'0');
    // if(flag_key)
    // {
    //   flag_key=0;
    //   test[0]=DIG_CODE[keyvalue];
    //   // Delay_5ms();
    //   for(i=20;i>=0;i--)
    //   {
    //     test[i]=test[i-1];
    //   }
    // }
    // Display_digital();
  //  led=flag;
  }
}
//void Display_digital()
//{
//  int i,j;
//  for(i=0;i<8;i++)
//  {
//    DIG_GPIO_DUAN=test[i];
//    DIG_GPIO_WEI=DIG_PLACE[i];
//    j=300;
//    while(j--);
//    DIG_GPIO_DUAN=0X00;
//  }
//}

//char Keydown(void)//按键
//{
//  GPIO_KEY=0X0F;
//  if(GPIO_KEY!=0X0F)
//  {
//    Delay_5ms();
//    if(GPIO_KEY!=0X0F)
//    {
//      flag_key=1;
//      GPIO_KEY=0X0F;
//      switch (GPIO_KEY)
//       {
//        case 0X07: keyvalue=0;  break;
//        case 0x0B: keyvalue=1;  break;
//        case 0x0D: keyvalue=2;  break;
//        case 0x0E: keyvalue=3;  break;
//      }
//      GPIO_KEY=0XF0;
//      switch (GPIO_KEY)
//      {
//        case 0X70: keyvalue+=0;  break;
//        case 0xB0: keyvalue+=4;  break;
//        case 0xD0: keyvalue+=8;  break;
//        case 0xE0: keyvalue+=12; break;
//      }
//      while(GPIO_KEY!=0XF0);
//    }
//  }
//  return keyvalue;
//}
//void Interrupt_Init(void) //外部中断初始化
//{
//  EA=1;
//  EX0=1;
//  IT0=1;//下降沿触发

//  EX1=1;
//  IT1=1;
//}
//void TIM_Init(void)//定时器初始化
//{
//  EA=1;
//  TMOD=0x01;//工作方式1
//  TH0=(65536-1000)/256;
//  TL0=(65536-1000)%256;
//  ET0=1;//打开定时器中断
//  TR0=1;//打开定时器0
//}
//void It0(void) interrupt 0
//{
//  EX0=0;
//  LCD1602_Writecom(0X01);
//  flag=~flag;
//  EX0=1;
//}
//void It1(void) interrupt 2
//{
//  EX1=0;
//  flag=1;
//  EX1=1;
//}
//void TIMER0 (void) interrupt 1
//{
//  TH0=(65536-1000)/256;
//  TL0=(65536-1000)%256;
//  timer++;
//  if(timer==1000)
//  {
//    P2=~P2;
//    timer=0;
//  }
//}
//void Usart_Init(void)
//{
//  EA=1;
//  ES=1;
//  TR1=1;
//  TMOD=0X20;
//  SCON=0X50;
//  TH1=0XFD;
//  TL1=0XFD;
//}
//void Usart_interrput(void) interrupt 4
//{
//  char buff;
//  if(RI)
//  {
//    RI=0;
//    // buff=SBUF;
//    // SBUF=buff;
//    uart_buff[uart_i]=SBUF;
//    uart_i++;
//  }
//  else
//    TI=0;
//}
// void Usart_pro()
// {
//   SBUF=uart_buff[];
// }
