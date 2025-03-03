void UART_INIT(void)
{
	SCON = 0x50;
	TMOD = 0x20;
	TH1=TL1=253;
	TR1 = 1;

}
void UART_TX(unsigned char d)
{
	SBUF=d;
	while(TI==0);
	TI=0;
}
void UART_STR(unsigned char *p)
{
	while(*p)
		UART_TX(*p++);
}

void UART_INT(int n)
{
	char a[9],i;
	for(i=0;n!=0;i++,n/=10)
		a[i]=n%10;
	for(--i;i>=0;i--)
		UART_TX(a[i]+48);
}

/*void main()
{
	uart_init();
		uart_tx('A');
	
	while(1);
}*/