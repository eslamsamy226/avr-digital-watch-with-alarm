
#include "std_macros.h"
#include <avr/io.h>
void DIO_vsetPINDir(unsigned char portname,unsigned char pinnumber,unsigned char direction){
	
	if (portname=='A')
	{
		if (direction)
		{
			SET_BIT(DDRA,pinnumber);
		}else{
			CLR_BIT(DDRA,pinnumber);
		}
	}
	
	
	if (portname=='B')
	{
		if (direction)
		{
			SET_BIT(DDRB,pinnumber);
		}else{
			CLR_BIT(DDRB,pinnumber);
		}
	}
	
	
	if (portname=='C')
	{
		if (direction)
		{
			SET_BIT(DDRC,pinnumber);
		}else{
			CLR_BIT(DDRC,pinnumber);
		}
	}
	
	
	if (portname=='D')
	{
		if (direction)
		{
			SET_BIT(DDRD,pinnumber);
		}else{
			CLR_BIT(DDRD,pinnumber);
		}
	}
		
}



void DIO_vwrite(unsigned char portname,unsigned char pinnumber,unsigned char outputvalue){
	
	if (portname=='A')
	{
		if (outputvalue)
		{
			SET_BIT(PORTA,pinnumber);
		}else{
			CLR_BIT(PORTA,pinnumber);
		}
	}
	
	
	if (portname=='B')
	{
		if (outputvalue)
		{
			SET_BIT(PORTB,pinnumber);
		}else{
			CLR_BIT(PORTB,pinnumber);
		}
	}
	
	
	if (portname=='C')
	{
		if (outputvalue)
		{
			SET_BIT(PORTC,pinnumber);
		}else{
			CLR_BIT(PORTC,pinnumber);
		}
	}
	
	
	if (portname=='D')
	{
		if (outputvalue)
		{
			SET_BIT(PORTD,pinnumber);
		}else{
			CLR_BIT(PORTD,pinnumber);
		}
	}
}


unsigned char DIO_u8read(unsigned char portname,unsigned char pinnumber){
	
	if (portname=='A')
	{
		return READ_BIT(PINA,pinnumber);
	}
	
	if (portname=='B')
	{
		return READ_BIT(PINB,pinnumber);
	}
	
	if (portname=='C')
	{
		return READ_BIT(PINC,pinnumber);
	}
	
	if (portname=='D')
	{
		return READ_BIT(PIND,pinnumber);
	}
	
	return 0;
}



void DIO_vtoggle(unsigned char portname,unsigned char pinnumber){
		if (portname=='A')
		{
			TOG_BIT(PORTA,pinnumber);
		}
		
		if (portname=='B')
		{
			TOG_BIT(PORTB,pinnumber);
		}
		
		if (portname=='C')
		{
			TOG_BIT(PORTC,pinnumber);
		}
		
		if (portname=='D')
		{
			TOG_BIT(PORTD,pinnumber);
		}
}

void DIO_vset_port_direction(unsigned char portname,unsigned char direction){
	
			if (portname=='A')
			{
				DDRA=direction;
			}			
			if (portname=='B')
			{
				DDRB=direction;
			}
			
			if (portname=='C')
			{
				DDRC=direction;
			}
			
			if (portname=='D')
			{
				DDRD=direction;
			}
}

void DIO_vwrite_port(unsigned char portname,unsigned char portvalue){
			if (portname=='A')
			{
				PORTA=portvalue;
			}
			if (portname=='B')
			{
				PORTB=portvalue;
			}
			
			if (portname=='C')
			{
				PORTC=portvalue;
			}
			
			if (portname=='D')
			{
				PORTD=portvalue;
			}
}




unsigned char DIO_u8read_port(unsigned char portname){
	
			if (portname=='A')
			{
				return PINA;
			}
			if (portname=='B')
			{
				return PINB;
			}
			
			if (portname=='C')
			{
				return PINB;
			}
			
			if (portname=='D')
			{
				return PIND;
			}
}



void DIO_vconnectpullup(char portname ,char pinnumber, char connect_pullup)
{
	switch(portname)
	{
		case 'A':
		if(connect_pullup==1)
		{
			SET_BIT(PORTA,pinnumber);
		}
		else
		{
			CLR_BIT(PORTA,pinnumber);
		}
		break;
		case 'B':
		if(connect_pullup==1)
		{
			SET_BIT(PORTB,pinnumber);
		}
		else
		{
			CLR_BIT(PORTB,pinnumber);
		}
		break;
		case 'C':
		if(connect_pullup==1)
		{
			SET_BIT(PORTC,pinnumber);
			
		}
		else
		{
			CLR_BIT(PORTC,pinnumber);
		}
		break;
		case 'D':
		if(connect_pullup==1)
		{
			SET_BIT(PORTD,pinnumber);
			
		}
		else
		{
			CLR_BIT(PORTD,pinnumber);
		}
		break;
		
	}
}



void DIO_vpin_output(char portname,char pinnumber){
	DIO_vsetPINDir(portname,pinnumber,1);
}

void DIO_vpin_input(char portname,char pinnumber){
		DIO_vsetPINDir(portname,pinnumber,0);
}

void write_low_nibble(unsigned char portname,unsigned char value)
{
	value&=0x0f;
	switch(portname)
	{
		case 'A':
		PORTA&=0xf0;
		PORTA|=value;
		case 'B':
		PORTB&=0xf0;
		PORTB|=value;
		case 'C':
		PORTC&=0xf0;
		PORTC|=value;
		case 'D':
		PORTD&=0xf0;
		PORTD|=value;
	}
}

void write_high_nibble(unsigned char portname,unsigned char value)
{
	value<<=4;
	switch(portname)
	{
		case 'A':
		PORTA&=0x0f;
		PORTA|=value;
		case 'B':
		PORTB&=0x0f;
		PORTB|=value;
		case 'C':
		PORTC&=0x0f;
		PORTC|=value;
		case 'D':
		PORTD&=0x0f;
		PORTD|=value;
	}
}	