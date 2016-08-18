#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define uchar unsigned char
void Sendlength(char *buff);
int intlen(int num);//计算int类型的数的长度
void Int_to_char(int num,char *buffer);//将整数拆开放入数组里
void sendstring(char *buffer);//发送数组
int main(void)
{
  int a=0x10;
  printf("%c\n",a);
  // char a[32]="ADas125";
  // sendstring(a);
//  Sendlength(a);
}
void Sendlength(char *buff)
{
	int length,count=0;
	length=strlen(buff);
	buff[0]=intlen(length) ;//发送数组的最高位数
  printf("length=%d\n",length);
  printf("buffer[0]=%d\n",buff[0]);
  Int_to_char(length,buff);
  for(int i=0;i<=buff[0]+1;i++)
   printf("buff[%d]=%d\n",i,buff[i]);
//	SEND_BUF(buff);
}
int intlen(int num)//计算int类型的数的长度
{
  int count=0;
  while(num)
  {
    count++;
    num/=10;
  }
  return count;
}
void Int_to_char(int num,char *buffer)//将整数拆开放入数组里
{
  int i=0;
  for(i=intlen(num);i>0;i--)
  {
    buffer[i]=num%10;
    printf("buffer[%d]=%d\n",i,buffer[i]);
    num/=10;
  }
}
void sendstring(char *buffer)//发送数组
{
  int i;
  char *buffer1;
  buffer1=(char*)malloc((strlen(buffer)+1)*sizeof(char));
	for(i=strlen(buffer)-1;i>=0;i--)
	{
		buffer1[i+1]=buffer[i];
	}
	buffer1[0]=strlen(buffer);
  for(i=0;i<strlen(buffer1);i++)
  printf("buffer1[%d]%c\n",i,buffer1[i]);
  printf("%d\n",sizeof(buffer1) );
}
