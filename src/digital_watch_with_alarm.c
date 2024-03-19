/*
 * digital_watch_with_alarm.c
 *
 * Created: 24/02/2024 09:25:17
 *  Author: Eslam
 */ 


#define __DELAY_BACKWARD_COMPATIBLE__


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "keypad.h"
#include "std_macros.h"
#include <avr/interrupt.h>
#include "Buzzer.h"

char hours=0,minutes=0,seconds=0;
char alarm_hours=0,alarm_minutes=0,alarm_seconds=0;
char on=0,buz=0;

void display_time(char r,char c,char *h,char *m,char *s){
	LCD_vSend_cmd(CURSOR_OF_DISPLAY_ON);
	LCD_movecursor(r,c);
	if (*s>=60)
	{
		*s=0;
		*m+=1;
	}
	if (*m>=60)
	{
		*m=0;
		*h+=1;
	}
	if (*h>=24)
	{
		*h=0;
	}
	LCD_vSend_char('0'+(*h/10));
	LCD_vSend_char('0'+(*h%10));
	LCD_vSend_char(':');
	LCD_vSend_char('0'+(*m/10));
	LCD_vSend_char('0'+(*m%10));
	LCD_vSend_char(':');
	LCD_vSend_char('0'+(*s/10));
	LCD_vSend_char('0'+(*s%10));
}

void timer1_CTC_init(){
	sei();
	OCR1A=31250;
	SET_BIT(TIMSK,OCIE1A);
	TCCR1B|=0x0c;
}
void timer0(){
	TCCR0=5;
	SET_BIT(TIMSK,TOIE0);
}

void set_time(char r,char c,char *h,char *m,char *s,char alm){


	unsigned char x=0;
	*h=0,*m=0,*s=0;
	display_time(r,(r==1?1:8),h,m,s);

	while(x<6){
		if (alm)
		{
			display_time(1,1,&hours,&minutes,&seconds);
		
		}
		LCD_movecursor(r,c);
		LCD_vSend_cmd(CURSOR_ON_DISPLAY_ON);
		
		 char y=keypad_u8check_press();
		 if (y!=0xff)
		 {
			 
			 _delay_ms(300);
			 if (x==0 && y>='0' && y<='2')
			 {
				*h+=(10*(y-'0'));
				x++;
				
				LCD_movecursor(r,++c);
			}else if (x==1 && ((*h==20 && y>='0' && y<='3') || (*h<20 && y>='0' && y<='9')))
			{
				*h+=(y-'0');
				 x++;
				 c++;
				 LCD_movecursor(r,++c);
			}else if (x==2 && y>='0' && y<='5')
			{
				*m+=(10*(y-'0'));
				 x++;
				 LCD_movecursor(r,++c);
			}else if (x==3 && y>='0' && y<='9')
			{
				
				*m+=((y-'0'));
				x++;
				c++;
				LCD_movecursor(r,++c);
		}else if (x==4 && y>='0' && y<='5')
		{
			*s+=(10*(y-'0'));
			x++;
			LCD_movecursor(r,++c);
		}else if (x==5 && y>='0' && y<='9')
		{
			
			*s+=((y-'0'));
			x++;
			c++;
			LCD_movecursor(r,++c);
		}
		
		display_time(r,(r==1?1:8),h,m,s);
			
	}			
	}
	
}

int main(void)
{
	LCD_vInit();
	keypad_vInit();
	Buzzer_vInit('C',0);
	LCD_movecursor(1,10);
	LCD_vSend_string("ALM:");
	LCD_vSend_string((on?"ON":"OFF"));
	LCD_movecursor(2,1);
	LCD_vSend_string("ALARM: ");
	display_time(2,8,&alarm_hours,&alarm_minutes,&alarm_seconds);
	display_time(1,1,&hours,&minutes,&seconds);
	set_time(1,1,&hours,&minutes,&seconds,0);
	
	timer1_CTC_init();
    while(1)
    {
		display_time(1,1,&hours,&minutes,&seconds);
		char st=keypad_u8check_press();
		if (st=='+')
		{
			_delay_ms(300);
			LCD_movecursor(1,14);
			set_time(2,8,&alarm_hours,&alarm_minutes,&alarm_seconds,1);	
			LCD_movecursor(1,14);
			LCD_vSend_string("ON ");
		}else if(st=='.'){
			_delay_ms(300);
			Buzzer_vOff('C',0);
			on=0;
			CLR_BIT(TIMSK,TOIE0);
			LCD_movecursor(1,14);
			alarm_hours=0,alarm_minutes=0,alarm_seconds=0;
			LCD_vSend_string("OFF");
			display_time(2,8,&alarm_hours,&alarm_minutes,&alarm_seconds);
			
		}
		
		if (alarm_hours==hours && alarm_minutes==minutes && alarm_seconds==seconds)
		{
			
			on=1;
			timer0();
			Buzzer_vOn('C',0);
			LCD_movecursor(1,14);
			LCD_vSend_string("UP ");
		}
		if (on)
		{
			
			if(buz>=30)
				Buzzer_vOff('C',0);
			if(buz>=45)
				Buzzer_vOn('C',0),buz=0;
			
		}
    }
}

ISR(TIMER1_COMPA_vect){
	seconds++;
}
ISR(TIMER0_OVF_vect){
	buz++;
}