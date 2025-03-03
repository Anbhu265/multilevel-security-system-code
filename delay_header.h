void delay_1ms(int ms);
void delay_1ms(int ms)
{
	unsigned char x;
	for(;ms>0;ms--)
	{
		for(x=250;x>0;x--);
		for(x=247;x>0;x--);
	}
}