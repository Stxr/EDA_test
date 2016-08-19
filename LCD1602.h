#ifndef __LCD1602_H_
#define __LCD1602_H_
#include<reg51.h>
#include "delay.h"
#include "string.h"
/*
数据位用P0口控制
WR:P2^5
RS：P2^6
LCDE:P2^7
*/
#define LCDDATA P0
#define L 0
#define H 1
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;
sbit LCD1602_E=P2^7;

void LCD1602_Writecom(char com);
void LCD1602_Init();
void LCD1602_Writedata(char dat);
void LCD1602_Writestring(char *s);//发送一个数组,c为从数组第s位开始发送
#endif
