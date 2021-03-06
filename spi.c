//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include "c8051f3xx.h"
#include "spi.h"
#include "delay.h"


//------------------------------------------------------------------------------------
// Global VARIABLES
//------------------------------------------------------------------------------------
bdata unsigned char dummy_bit;
sbit dummy_bit7 = dummy_bit^7;
sbit dummy_bit6 = dummy_bit^6;
sbit dummy_bit5 = dummy_bit^5;
sbit dummy_bit4 = dummy_bit^4;
sbit dummy_bit3 = dummy_bit^3;
sbit dummy_bit2 = dummy_bit^2;
sbit dummy_bit1 = dummy_bit^1;
sbit dummy_bit0 = dummy_bit^0;


//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void spi_init(void);
//unsigned char spi_read_byte(void);
//void spi_write_byte(unsigned char data_in);
unsigned char spi_transfer(unsigned char data_in);
unsigned char spi_read_eeprom(unsigned int addr);
void spi_write_eeprom(unsigned int addr, unsigned char data_in);
unsigned char spi_read_sensor(unsigned char addr);
void spi_write_sensor(unsigned char addr, unsigned char data_in);


//------------------------------------------------------------------------------------
// InitSeq
//------------------------------------------------------------------------------------
void spi_init(void)
{
	EA = 0;
	NCS = 1;
	SCLK = 1;
	MISO = 1;
	MOSI = 1;
	EE_NCS = 1;
    P0MDOUT   = 0x5A;
	EA = 1;
}


//------------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------------
/*
unsigned char spi_read_byte(void)
{
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit7 = MISO;

	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit6 = MISO;

	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit5 = MISO;

	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit4 = MISO;
	
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit3 = MISO;

	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit2 = MISO;

	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit1 = MISO;

	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit0 = MISO;

	return dummy_bit;
}
*/


/*
void spi_write_byte(unsigned char data_in)
{
//	P0MDOUT |= 0x08;
	dummy_bit = data_in;
	
	SCLK = 0;
	MOSI = dummy_bit7;	delay1();
	SCLK = 1;	delay1();

	SCLK = 0;
	MOSI = dummy_bit6;	delay1();
	SCLK = 1;	delay1();

	SCLK = 0;
	MOSI = dummy_bit5;	delay1();
	SCLK = 1;	delay1();

	SCLK = 0;
	MOSI = dummy_bit4;	delay1();
	SCLK = 1;	delay1();

	SCLK = 0;
	MOSI = dummy_bit3;	delay1();
	SCLK = 1;	delay1();

	SCLK = 0;
	MOSI = dummy_bit2;	delay1();
	SCLK = 1;	delay1();

	SCLK = 0;
	MOSI = dummy_bit1;	delay1();
	SCLK = 1;	delay1();

	SCLK = 0;
	MOSI = dummy_bit0;	delay1();
	SCLK = 1;	delay1();

//	P0MDOUT &= ~0x08;
	MOSI = 1;
}
*/


unsigned char spi_transfer(unsigned char data_in)
{
	dummy_bit = data_in;
	MOSI = dummy_bit7;
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit7 = MISO;

	MOSI = dummy_bit6;
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit6 = MISO;

	MOSI = dummy_bit5;
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit5 = MISO;

	MOSI = dummy_bit4;
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit4 = MISO;

	MOSI = dummy_bit3;
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit3 = MISO;

	MOSI = dummy_bit2;
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit2 = MISO;

	MOSI = dummy_bit1;
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit1 = MISO;

	MOSI = dummy_bit0;
	SCLK = 0;	delay1();
	SCLK = 1;	delay1();
	dummy_bit0 = MISO;

	return dummy_bit;
}


unsigned char spi_read_eeprom(unsigned int addr)
{
	unsigned char temp;
	EE_NCS = 0;
	if((addr & 0x0100) == 0x0100)
	{
		temp = (READ_DATA | 0x08);
	}
	else
	{
		temp = READ_DATA;
	}
	spi_transfer(temp);
	spi_transfer((unsigned char)addr);
	temp = spi_transfer(0xff);
	EE_NCS = 1;

	return temp;
}


void spi_write_eeprom(unsigned int addr, unsigned char data_in)
{
	unsigned char temp;

	EE_NCS = 0;
	delay1();
	spi_transfer(WRITE_ENABLE);
	EE_NCS = 1;

	delay_us(300);

	EE_NCS = 0;
	delay1();
	if((addr & 0x0100) == 0x0100)
	{
		temp = (WRITE_DATA | 0x08);
	}
	else
	{
		temp = WRITE_DATA;
	}
	spi_transfer(temp);
	delay1();
	spi_transfer((unsigned char)addr);
	delay1();
	spi_transfer(data_in);
	delay1();
	EE_NCS = 1;
}


unsigned char spi_read_sensor(unsigned char addr)
{
	unsigned char temp;
	NCS = 0;
	delay1();
	spi_transfer(addr);
	delay_us(100);
	temp = spi_transfer(0xff);
	delay_us(120);
	NCS = 1;

	return temp;
}


void spi_write_sensor(unsigned char addr, unsigned char data_in)
{
	NCS = 0;
	delay1();
	spi_transfer(addr | 0x80);
	delay_us(50);
	spi_transfer(data_in);
	delay_us(30);
	NCS = 1;
}





