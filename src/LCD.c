#include <avr/io.h>
#include "LCD.h"
#define  F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
void LCD_vInit(void){
	_delay_ms(100);
	DIO_vsetPINDir(CONTROL_PORT,EN,1);
	DIO_vsetPINDir(CONTROL_PORT,RS,1);
	DIO_vsetPINDir(CONTROL_PORT,RW,1);
	#ifdef eight_bits_mode
	DIO_vset_port_direction(DATA_PORT,0xff);
	LCD_vSend_cmd(EIGHT_BITS); //8 bit mode
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAY_ON);//display on cursor on
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); //entry mode
	
	#else
	DIO_vsetPINDir(DATA_PORT,4,1);
	DIO_vsetPINDir(DATA_PORT,5,1);
	DIO_vsetPINDir(DATA_PORT,6,1);
	DIO_vsetPINDir(DATA_PORT,7,1);
	LCD_vSend_cmd(RETURN_HOME); //return home
	_delay_ms(10);
	LCD_vSend_cmd(FOUR_BITS); //4bit mode
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_OF_DISPLAY_ON);//display on cursor on
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); //entry mode
	_delay_ms(1);
	#endif

}


void LCD_vSend_cmd(char cmd){
	
	DIO_vwrite(CONTROL_PORT,RS,0);
	#ifdef eight_bits_mode
	DIO_vwrite_port(DATA_PORT,cmd);
	send_falling_edge();
	#else
	write_high_nibble(DATA_PORT,cmd>>4);
	DIO_vwrite(CONTROL_PORT,RS,0);
	send_falling_edge();
	write_high_nibble(DATA_PORT,cmd);
	DIO_vwrite(CONTROL_PORT,RS,0);
	send_falling_edge();
	#endif
	_delay_ms(1);
}
void LCD_vSend_char(char data){
	
	DIO_vwrite(CONTROL_PORT,RS,1);
	#ifdef eight_bits_mode
	DIO_vwrite_port(DATA_PORT,data);
	send_falling_edge();
	#else
	write_high_nibble(DATA_PORT,data>>4);
	send_falling_edge();
	write_high_nibble(DATA_PORT,data);
	send_falling_edge();
	#endif
	_delay_ms(1);
}

static void send_falling_edge()
{
	DIO_vwrite(CONTROL_PORT,EN,1);
	_delay_ms(2);
	DIO_vwrite(CONTROL_PORT,EN,0);
	_delay_ms(2);
}

void LCD_vSend_string(char *data){
	
	while(*data != '\0' )
	{
		LCD_vSend_char(*data);
		data++;
	}
}

void LCD_clearscreen()
{
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
}

void LCD_movecursor(char row,char coloumn)
{
	char data ;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_vSend_cmd(data);
	_delay_ms(1);
}



void LCD_store_custom_char(unsigned char location,char custom_char[]){
	
	LCD_vSend_cmd(64+(location-1)*8);
	
	for (char i=0;i<8;i++)
	{
		LCD_vSend_char(custom_char[i]);
	}
}


void LCD_diplay_custom_char(unsigned char location){
	LCD_vSend_char(location-1);
}
