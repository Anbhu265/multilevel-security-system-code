#include<reg51.h>
#include"delay_header.h"
#define LCD P2
sbit RS=P1^0;
sbit RW=P1^1;
sbit E=P1^2;

void LCD_CMD(unsigned char cmd)
{
	LCD = cmd;
	RS=0;
	RW=0;
	E=1;
	delay_1ms(2);
	E=0;
}
void LCD_INIT()
{
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0c);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
}
void LCD_DATA(unsigned char d)
{
	LCD=d;
	RS=1;
	RW=0;
	E=1;
	delay_1ms(2);
	E=0;
	//uart_tx(d);
}
void LCD_STR(unsigned char *p)
{
	while(*p)
		LCD_DATA(*p++);
}
void LCD_INT(int n)
{
	char a[9],i;
	for(i=0;n!=0;i++,n/=10)
		a[i]=n%10;
	for(--i;i>=0;i--)
		LCD_DATA(a[i]+48);
}
void LCD_FLOAT(float n)
{
	int te;
	if(n<0)
	{
		n=-n;
		LCD_DATA('-');	
	}
	te=n;
	LCD_INT(te);
	LCD_DATA('.');
	LCD_INT(((n-te)*100));
	LCD_DATA(' ');
}
