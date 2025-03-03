#include<reg51.h>

sbit scl = P3^2;
sbit sda = P3^3;
extern void lcd_data(unsigned char);


extern void delay_1ms(int);

void i2c_start(void)
{
	scl =1;
	sda =1;
	sda =0;
}

void i2c_stop(void)
{
	
	sda =0; 
	scl =1;
	sda =1;
}

void i2c_bytewrite(unsigned char d)
{
	unsigned char j;
	for(j=0;j<8;j++)
	{
		scl = 0;
  	sda = d&(0x80>>j);
		scl = 1;
	}
}

unsigned char i2c_byteread(void)
{
	unsigned char j,buf=0;
	//sda=1;
	for(j=0;j<8;j++)
	{
		
	  scl =0; 	
  	scl =1;		
		if(sda)
			buf|=(0x80>>j);
   
	}
	return buf;
}

void i2c_ack(void)
{
	scl =0;
	sda =1;
	scl =1;
	while(sda==1);
	scl =0;
}

void i2c_noack(void)
{
	scl =0;
	sda =1;
	scl =1;
}

void i2c_slave_write(unsigned char sa,
                     unsigned char r_addr,
                     unsigned char dat)
{
	i2c_start();
	i2c_bytewrite(sa);
	i2c_ack();
	i2c_bytewrite(r_addr);
	i2c_ack();
	i2c_bytewrite(dat);
	i2c_ack();
	i2c_stop();
	delay_1ms(10);
}

unsigned char i2c_slave_read(unsigned char sa,
                              unsigned char r_addr)
{
	unsigned char buff;
	//dummy write
	i2c_start();
	i2c_bytewrite(sa);
	i2c_ack();
	i2c_bytewrite(r_addr);
	i2c_ack();
	
	//read operation
	i2c_start();
	i2c_bytewrite(sa|1);
	i2c_ack();
	buff=i2c_byteread();
	i2c_noack();
	scl =0; 
	i2c_stop();
	return buff;
}

/*void i2c_current_addr_read(unsigned char sa)
{
	unsigned char buff1,buff2;
	//dummy write
	i2c_start();
	i2c_bytewrite(sa|1);
	scl =0;
	sda =0;
	scl =1;
	//scl =0;
	//i2c_ack();
	
	//read operation
	buff1=i2c_byteread();
	scl =0;
	sda =0;
	scl =1;
	//scl =0;
	//i2c_ack();
	buff2=i2c_byteread();
	scl =0;
	sda =1;
	scl =1;
	
	//i2c_noack();
	scl =0; 
	i2c_stop();
	lcd_data(buff1);
	lcd_data(buff2);
	
	
	//return buff;
}

*/