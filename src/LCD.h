

#ifndef LCD_H_
#define LCD_H_
#include "DIO.h"
#include "LCD_config.h"
#define DATA_PORT 'B'
#define CONTROL_PORT 'D'
#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAY_ON 0x0e
#define CURSOR_OF_DISPLAY_ON 0x0c
#define CURSOR_BLINK_DISPLAY_ON 0x0f
#define SHIFT_LEFT 0x18
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06

#define FOUR_BITS 0x28

#define EN 3
#define RS 1
#define RW 2
#define EIGHT_BITS 0x38

void LCD_vInit(void);
static void send_falling_edge(void);
void LCD_vSend_cmd(char cmd);
void LCD_vSend_char(char data);
void LCD_vSend_string(char *data);
void LCD_clearscreen();
void LCD_movecursor(char row,char coloumn);


void LCD_store_custom_char(unsigned char location,char custom_char[]);


void LCD_diplay_custom_char(unsigned char location);
#endif /* LCD_H_ */