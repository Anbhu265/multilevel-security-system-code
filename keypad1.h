#include<reg51.h>
sbit C0=P0^0;
sbit C1=P0^1;
sbit C2=P0^2;
sbit C3=P0^3;
sbit R0=P0^4;
sbit R1=P0^5;
sbit R2=P0^6;
sbit R3=P0^7;
code unsigned int key[4][4]={'1','2','3','4','5','6','7','8','9','0','#','+','/','*','-','%'};
unsigned int otp=1000;
char keymain()
{	
	unsigned int row_val,col_val;
	//while(1)
	{
	R0=R1=R2=R3=0;
	C0=C1=C2=C3=1;
		do{
			if(otp==9999)
				otp=1000;
			otp++;
		}while(C0&C1&C2&C3);//waiting for key pressed
	// row 0
	R0=0;
	R1=R2=R3=1;
	if((C0&C1&C2&C3)==0)
	{
		row_val=0;
		goto col_check;
	}
	// row 1
	R1=0;
	R0=R2=R3=1;
	if((C0&C1&C2&C3)==0)
	{
		row_val=1;
		goto col_check;
	}
	// row 2
	R2=0;
	R0=R1=R3=1;
	if((C0&C1&C2&C3)==0)
	{
		row_val=2;
		goto col_check;
	}
	// row 3
	R3=0;
	R0=R1=R2=1;
	if((C0&C1&C2&C3)==0)
	{
		row_val=3;
		goto col_check;
	}
	col_check:
		if(C0==0)
			col_val=0;
		else if(C1==0)
			col_val=1;
		else if(C2==0)
			col_val=2;
		else if(C3==0)
			col_val=3;
		
		delay_1ms(300);
	while((C0&C1&C2&C3)==0);
			delay_1ms(300);
		return key[row_val][col_val];
}
}