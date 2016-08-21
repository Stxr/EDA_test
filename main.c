#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "I2C.h"
#include "EEPROM.h"
#include "NRF2401.h"
//#define GPIO_KEY P1
#define DIG_GPIO_DUAN P1
#define DIG_GPIO_WEI P0
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit NRF_IR  = P3^5;

unsigned char rece_buf[32];
unsigned char code DIG_PLACE[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//位选控制   查表的方法控制
unsigned char code DIG_CODE[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};  //0~F的显示码


int main(void)
{
  unsigned char count,i,flag_4=1; //flag_4读取标志位，避免重复读取
//  unsigned char rece_buf[32]="8>52103876cADf857";
  LCD1602_Init();// LCD初始化
	while(NRF24L01_Check()); // 等待检测到NRF24L01，程序才会向下执行
  NRF24L01_RT_Init();
  while(1)
  {
  	if(NRF_IR==0)	 	// 如果无线模块接收到数据
  	{
  		if(NRF24L01_RxPacket(rece_buf)==0)
  		{
        if(rece_buf[1]!='>')
        {
          sendstring("Please start with >\n");
        }
        else
        {
          if(rece_buf[2]!='5'&&\
          rece_buf[3]!='2'&&\
          rece_buf[4]!='1'&&\
          rece_buf[5]!='0'
          )return -1;
          else
          {
            switch (rece_buf[6])
             {
              case '1':   //显示发送数据并把数据保存到EEPROM里面
                        sendstring("display and save data\n");
                        LCD1602_Writecom(0X01);
                        LCD1602_Writestring("Write:");
                        LCD1602_Writestring(rece_buf+7);//从第七位开始显示数据,把第七位的地址传给指针
                        AT24C02_writestring(rece_buf+7);//从第七位开始保存数据,把第七位的地址传给指针
                        flag_4=1;
                        break;
              case '2':  //屏幕左移
                        sendstring("move left\n");
                      //  LCD1602_Writestring(rece_buf+7);//从第七位开始显示数据,把第七位的地址传给指针
                        for(count=0;count<14;count++)
                        {
                          LCD1602_Writecom(0X18);//整屏左移
                          Delay_100ms();
                        }
                        break;
              case '3'://用数码管显示数据
                        sendstring("Display on the digital_control\n");
                        LCD1602_Writecom(0X01);
                        LCD1602_Writestring("Display on the ");
                        LCD1602_Writecom(0x80+0x40);
                        LCD1602_Writestring("digital_control");
                        while (rece_buf[6]=='3')
                        {
                          NRF24L01_RxPacket(rece_buf);
                          for(count=0;count<8;count++)
                          {
                            switch(count)	 //位选，选择点亮的数码管，
                            {
                              case(0):
                              LSA=0;LSB=0;LSC=0; break;//显示第0位
                              case(1):
                              LSA=1;LSB=0;LSC=0; break;//显示第1位
                              case(2):
                              LSA=0;LSB=1;LSC=0; break;//显示第2位
                              case(3):
                              LSA=1;LSB=1;LSC=0; break;//显示第3位
                              case(4):
                              LSA=0;LSB=0;LSC=1; break;//显示第4位
                              case(5):
                              LSA=1;LSB=0;LSC=1; break;//显示第5位
                              case(6):
                              LSA=0;LSB=1;LSC=1; break;//显示第6位
                              case(7):
                              LSA=1;LSB=1;LSC=1; break;//显示第7位
                            }
                            if(rece_buf[count+7]<='9')
                            DIG_GPIO_DUAN=DIG_CODE[rece_buf[count+7]-'0'];
                            else if(rece_buf[count+7]<='f'&&rece_buf[count+7]>='a')
                            DIG_GPIO_DUAN=DIG_CODE[rece_buf[count+7]-'a'+10];
                            else if(rece_buf[count+7]<='F'&&rece_buf[count+7]>='A')
                            DIG_GPIO_DUAN=DIG_CODE[rece_buf[count+7]-'A'+10];
                            i=500;  //消抖
                            while(i--);
                          }
                        }
                        break;
              case '4'://从EEPROM中读取数据，并用LCD1602显示出来
                        sendstring("display and read from EEPROM\n");
                        LCD1602_Writecom(0X01);
                        LCD1602_Writestring("Read:");
                        for(count=0;rece_buf[count+7]!='\0';count++)
                        {
                          LCD1602_Writedata(AT24C02_read(count));
                        }
                        flag_4=0;
                        break;
              default :
                        sendstring("The fifth number error (0-4)\n");
                        break;
            }
          }
        }
 		   }
 	   }
   }
}
