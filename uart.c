//To receive and re-transmit through UART0 of LPC2129
#include<LPC21xx.h>
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);
void UART0_STR(unsigned char *);
int main()
{
	//unsigned char ret;
	UART0_CONFIG();
	//UART0_TX('A');
UART0_STR("EMBEDDED");
	//while(1)
//	{
	//	ret=UART0_RX();
	//	UART0_TX(ret);
	//}
}
void UART0_CONFIG(void)
{
	PINSEL0 |=0X00000005;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}
void UART0_TX(unsigned char d)
{
	while(!(U0LSR&(1<<5)));
	U0THR=d;
}
void UART0_STR(unsigned char *s)
{
	while(*s)
	UART0_TX(*s++);
}
unsigned char UART0_RX(void)
{
	while(((U0LSR&(1<<0)))==0);
	return U0RBR;
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