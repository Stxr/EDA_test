#include "keydown.h"
char flag_key=0,keyvalue;
char Keydown(void)
{
  GPIO_KEY=0X0F;
  if(GPIO_KEY!=0X0F)
  {
    Delay_1ms();
    if(GPIO_KEY!=0X0F)
    {
      flag_key=1;
      switch (GPIO_KEY)
       {
        case 0X07: keyvalue=0;  break;
        case 0x0B: keyvalue=1;  break;
        case 0x0D: keyvalue=2;  break;
        case 0x0E: keyvalue=3;  break;
        default  : break;
      }
      GPIO_KEY=0XF0;
      switch (GPIO_KEY)
      {
        case 0X70: keyvalue+=0;  break;
        case 0xB0: keyvalue+=4;  break;
        case 0xD0: keyvalue+=8;  break;
        case 0x0E: keyvalue+=12; break;
        default  : break;
      }
      while(GPIO_KEY!=0XF0);
    }
  }
  return keyvalue;
}
