#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "I2C.h"
#include "EEPROM.h"
#include "NRF2401.h"
#define GPIO_KEY P1
#define DIG_GPIO_DUAN P3
#define DIG_GPIO_WEI P1

sbit NRF_IR  = P0^2;

unsigned char rece_buf[32];
unsigned char code DIG_PLACE[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//位选控制   查表的方法控制
unsigned char code DIG_CODE[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};  //0~F的显示码


int main(void)
{
  unsigned char count,i,flag_4=1;
  unsigned char rece_buf[32]="8>52104876cADf857";
  LCD1602_Init();// LCD初始化
//	while(NRF24L01_Check()); // 等待检测到NRF24L01，程序才会向下执行
  NRF24L01_RT_Init();
  // LCD1602_Writestring(test+7);
  while(1)
  {

  	if(NRF_IR==0)	 	// 如果无线模块接收到数据
  	{
  		// if(NRF24L01_RxPacket(rece_buf)==0)
  		{
        if(rece_buf[1]!='>')
        {
          sendstring("Please start with >\n");
        }
        else if(rece_buf[2]!='5'&&\
                rece_buf[3]!='2'&&\
                rece_buf[4]!='1'&&\
                rece_buf[5]!='0'
               )return -1;
        if(rece_buf[6]=='1')//显示发送数据并把数据保存到EEPROM里面
        {
          LCD1602_Writestring("Write:");
          LCD1602_Writestring(rece_buf+7);//从第七位开始显示数据,把第七位的地址传给指针
          AT24C02_writestring(rece_buf+7);//从第七位开始保存数据,把第七位的地址传给指针
          flag_4=1;
        }
        else if(rece_buf[6]=='2')//屏幕左移
        {
            LCD1602_Writestring(rece_buf+7);//从第七位开始显示数据,把第七位的地址传给指针
            for(count=0;count<14;count++)
            {
              LCD1602_Writecom(0X18);//整屏左移
              Delay_500ms();
            }
        }
        else if(rece_buf[6]=='3')//用数码管显示数据
        {
          for(count=0;count<8;count++)
          {
            DIG_GPIO_WEI=DIG_PLACE[count];
            if(rece_buf[count+7]<='9')
              DIG_GPIO_DUAN=DIG_CODE[rece_buf[count+7]-'0'];
            else if(rece_buf[count+7]<='f'&&rece_buf[count+7]>='a')
              DIG_GPIO_DUAN=DIG_CODE[rece_buf[count+7]-'a'+10];
            else if(rece_buf[count+7]<='F'&&rece_buf[count+7]>='A')
              DIG_GPIO_DUAN=DIG_CODE[rece_buf[count+7]-'A'+10];
            i=500;
            while(i--);
          }
        }
        else if (rece_buf[6]=='4')//从EEPROM中读取数据，并用LCD1602显示出来
        {
          if(flag_4)
          {
            LCD1602_Writestring("Read:");
            for(count=0;rece_buf[count+7]!='\0';count++)
            {
              LCD1602_Writedata(AT24C02_read(count));
            }
            flag_4=0;
          }
        }
        else
        {
          sendstring("Please check the fifth character(0-4)\n");
        }
 		   }
 	   }
   }
}
