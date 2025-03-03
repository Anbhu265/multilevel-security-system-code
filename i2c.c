#include<reg51.h>
#include"testing_i2c.c"
#include"lcd.c"

void main()
{
	unsigned char a;
	LCD_INIT();
	//LCD_DATA('C');
	i2cDevwrite(0xA0,0x00,'A');
	while(1);
}