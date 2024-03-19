/*
 * Buzzer.c
 *
 * Created: 24/01/2024 14:17:59
 *  Author: Eslam
 */ 


#include <avr/io.h>
#include "DIO.h"

void Buzzer_vInit(char portname,char pinnumber){
	DIO_vsetPINDir(portname,pinnumber,1);
}

void Buzzer_vOn(char portname,char pinnumber){
	DIO_vwrite(portname,pinnumber,1);
}

void Buzzer_vOff(char portname,char pinnumber){
		DIO_vwrite(portname,pinnumber,0);
}
