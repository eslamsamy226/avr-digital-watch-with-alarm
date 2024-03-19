/*
 * keypad.c
 *
 * Created: 09/02/2024 14:43:56
 *  Author: Eslam
 */ 


#include "keypad.h"
#include "util/delay.h"
	
char arr[4][4]={{'7','8','9','/'},
					{'4','5','6','*'},
					{'1','2','3','-'},
					{'.','0','=','+'}};
void keypad_vInit(){
	
	
	DDRA=0;
	DDRA|=0x0f;
	PORTA=0Xff;
		
}
char keypad_u8check_press(){

			char row,coloumn,x;
			char returnval=NOTPRESSED;
			for(row=0;row<4;row++)
			{
				DIO_vwrite('A',row,0);
				
				
			for(coloumn=0;coloumn<4;coloumn++)
			{
				x=DIO_u8read('A',(coloumn+4));
				if(x==0)
				{
					returnval=arr[row][coloumn];
					break;
				}
			}
			DIO_vwrite('A',row,1);
			
			if(x==0)
			{
				break;
			}
		}
		return returnval ;
}