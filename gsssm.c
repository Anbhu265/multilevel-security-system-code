#include<reg51.h>
//#include"delay_header.h"
#include"lcd1.c"
#include"uart1.h"
#include"keypad1.h"
#include"testing_i2c.c"
sbit M1 = P1^3;
sbit M2 = P1^4;
void main()
{
	unsigned int n1,n2=0,i=0,cc=0,n3=0,n4=0;
	char ch,pas[4]={1,2,3,4},j;
	LCD_INIT();

	UART_INIT();

for(i=0;i<4;i++)
	{
		i2c_slave_write(0xa0,0x00+i,pas[i]);
	}
	LCD_CMD(0X84);
	LCD_CMD(0x01);
	LCD_STR("MULTILEVEL");
	LCD_CMD(0XC0);
	LCD_STR("SECURITY SYSTEM");
	delay_1ms(4000);
	LCD_CMD(0x01);
	LCD_STR("Press *");
	while(keymain()!='*');
	for(i=0;i<4;i++)
	{
		ch=i2c_slave_read(0xa0,0x00+i);
		n3=n3*10+ch;
	}
	LCD_INT(n3);
	for(j=0;j<3;j++)
	{
		LCD_CMD(0x01);
		LCD_STR("PASSWORD");
		LCD_CMD(0xc0);
	for(i=0;i<4;i++)
		{
			ch=keymain();
			LCD_DATA('*');
			n4=n4*10+(ch-48);	
		}
		if(n3==n4)
			break;
		else
		{
			LCD_CMD(0x01);
			LCD_STR("WRONG");
			delay_1ms(2000);
		}
			
	}
	if(j==3)
	{
		/*UART_STR("AT+CMGS=\"+91****\"\r\n");
		delay_1ms(100);
		UART_STR("ALERT !!!\n SOMEONE TRY TO OPEN THE DOOR");
		UART_TX(0x1a);	//to enter (ctrl+z)
		delay_1ms(100);*/
		LCD_CMD(0x01);
		LCD_STR("ACCESS DEINED...");	
		/*LCD_CMD(0xc0);
		LCD_STR("Police is comming...");*/
		while(1);
	}
	
	LCD_CMD(0x01);
	LCD_STR("OTP sending ...!");
	delay_1ms(1000);
	n1=otp;
	UART_STR("AT+CMGF=1\r\n");
	delay_1ms(100);
	UART_STR("AT+CMGS=\"+918907150576\"\r\n");
	delay_1ms(100);
	UART_INT(n1);
	UART_TX(0x1a);	//to enter (ctrl+z)
	//delay_1ms(100);
	label:
		LCD_CMD(0x01);
		LCD_STR("Enter the OTP...");
		LCD_CMD(0xc0);
		for(i=0;i<4;i++)
		{
		ch=keymain();
		LCD_DATA('*');
		n2=n2*10+(ch-48);	
		}
	delay_1ms(50);
	LCD_CMD(0x01);
	
	if(n1==n2)
	{
		LCD_STR("OTP MATCHED...");
		delay_1ms(1000);
		LCD_CMD(0x01);
		LCD_STR("DOOR OPENING");
		delay_1ms(1000);
		M1=0,M2=1;
		delay_1ms(5000);
			M1=1,M2=1;
		LCD_STR("DOOR OPENED");
		delay_1ms(100);	
		for(i=5;i>0;i--)
		{
				LCD_CMD(0x01);
			LCD_STR("DOOR CLOSING");
			LCD_CMD(0xc0);
		LCD_STR("AFTER ");
			LCD_DATA(i+48);
			LCD_STR(" SECONDS");
		delay_1ms(750);
		}
			M1=1,M2=0;
			LCD_CMD(0x01);
		LCD_STR("DOOR CLOSING");
		delay_1ms(4000);
			M1=1,M2=1;
		LCD_CMD(0x01);
		LCD_STR("DOOR CLOSED");
		delay_1ms(1000);
	}
	else
	{
		LCD_CMD(0x01);
		LCD_STR("INVALID OTP !!..");
		delay_1ms(1000);
		cc++;
		if(cc==3)
		{
			UART_STR("AT+CMGS=\"+918907150576\"\r\n");
			delay_1ms(100);
				UART_STR("ALERT !!!\n SOMEONE TRY TO OPEN THE DOOR");
			UART_TX(0x1a);	//to enter (ctrl+z)
			delay_1ms(100);
			LCD_CMD(0x01);
			LCD_STR("ACCESS DEINED...");	
			LCD_CMD(0xc0);
			LCD_STR("Police is comming...");
			while(1);
		}
		else	
		{		
			n2=0;	
		goto label;
		}
	}
	LCD_CMD(0x01);
	LCD_STR("THANK YOU");
/*	LCD_CMD(0xc0);
	LCD_STR("....WELCOME....");*/
	while(1);
	
}