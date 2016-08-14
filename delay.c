#include "delay.h"
void Delay_10us(void)   //误差 0us
{
  unsigned char a,b;
  for(b=1;b>0;b--)
  for(a=2;a>0;a--);
}
void Delay_100us(void)   //误差 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=47;a>0;a--);
}
void Delay_1ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}
void Delay_5ms(void)   //误差 0us
{
    unsigned char a,b;
    for(b=19;b>0;b--)
        for(a=130;a>0;a--);
}
void Delay_10ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}
void Delay_100ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=19;c>0;c--)
        for(b=20;b>0;b--)
            for(a=130;a>0;a--);
}
void Delay_500ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
}
