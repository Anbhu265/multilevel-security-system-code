//#include<LPC21xx.h>
#include"DELL.C"
#define LCD_D 0xff<<2//p0.0 to  p0.7
#define RS 1<<17//p0.17
#define RW 1<<18//p0.18
#define EN 1<<19//p0.19
typedef unsigned char U8;
//void lcd_integer(signed int);
void lcd_init(void);
void lcd_cmd(U8);
void lcd_data(U8);
void str(unsigned char*);

void lcd_init(void)
{
	IODIR0=LCD_D|RS|EN|RW;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x38);
	lcd_cmd(0x0c);
	lcd_cmd(0x80);
}
void lcd_cmd(U8 c)
{
	IOCLR0=LCD_D|RS|EN|RW;
	IOSET0=c<<2;
	IOCLR0=RS;
	IOCLR0=RW;
	IOSET0=EN;
	delay(50);
	IOCLR0=EN;
}
void lcd_data(U8 d)
{
	IOCLR0=LCD_D|RS|EN|RW;
	IOSET0=d<<2;
	IOSET0=RS;
	IOCLR0=RW;
	IOSET0=EN;
	delay(50);
	IOCLR0=EN;
}

void str(unsigned char *dat)
{
	while(*dat!='\0')
	{
		lcd_data(*dat);
		dat++;
	}
}



void lcd_integer(signed int num)
{
	unsigned char arr[5];
	signed char i=0;
	if(num==0)
		lcd_data('0');
	else
	{
		if(num<0)
		{
			lcd_data('-');
			num=-num;
		}
	while(num>0)
	{
		arr[i++]=(num%10)+48;
		num=num/10;
	}
	for(--i;i>=0;i--)
	lcd_data(arr[i]);
}
}



