#include "LCD1602.h"

void LCD1602_Writecom(char com)
{
  LCD1602_RS=L;
  LCD1602_RW=L;
  LCD1602_E=L;

  LCDDATA=com;
  Delay_5ms();
  LCD1602_E=H;
  Delay_5ms();
  LCD1602_E=L;
}
void LCD1602_Writedata(char dat)
{
  LCD1602_RS=H;
  LCD1602_RW=L;
  LCD1602_E=L;

  LCDDATA=dat;
  Delay_5ms();
  LCD1602_E=H;
  Delay_5ms();
  LCD1602_E=L;
}
void LCD1602_Init()
{
  LCD1602_Writecom(0X38);//显示模式
  LCD1602_Writecom(0X0C);//开显示不显示光标
  LCD1602_Writecom(0X06);//当输入一个字符，光标自动向后移动一位
  LCD1602_Writecom(0X01);//清屏
  LCD1602_Writecom(0X80);//指针起点
}
void LCD1602_Writestring(char *s)
{
  char p;
  for(p=0;s[p]!='\0';p++)
  {
    LCD1602_Writedata(s[p]);
    // Delay_500ms();
  }
}
