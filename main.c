#include <reg51.h>
#include "delay.h"
#include "LCD1602.h"
#include "keydown.h"
char test[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int main(void)
{
  LCD1602_Init();
  LCD1602_Writedata(test[keydown()]);
  while(1);
}
