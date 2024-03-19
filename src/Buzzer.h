/*
 * Buzzer.h
 *
 * Created: 24/01/2024 14:18:22
 *  Author: Eslam
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_


void Buzzer_vInit(char portname,char pinnumber);

void Buzzer_vOn(char portname,char pinnumber);

void Buzzer_vOff(char portname,char pinnumber);

//void Buzzer_caren(char portname,char pinnumber);

#endif /* BUZZER_H_ */