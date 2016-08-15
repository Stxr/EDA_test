#ifndef __KEYDOWN_H_
#define __KEYDOWN_H_
/*
IO:P3
*/
#include "delay.h"
#include "reg51.h"
#define GPIO_KEY P3
static char flag_key=0;
static char keyvalue;
char Keydown(void);
#endif
