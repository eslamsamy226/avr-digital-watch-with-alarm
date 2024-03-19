/*
 * keypad.h
 *
 * Created: 09/02/2024 14:44:26
 *  Author: Eslam
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


#define NOTPRESSED 0xff
#include "DIO.h"
#include "ports.h"
void keypad_vInit();
char keypad_u8check_press();


#endif /* KEYPAD_H_ */