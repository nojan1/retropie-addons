/*
 * Fan.c
 *
 * Created: 2015-05-28 08:29:45
 *  Author: hedlundn
 */ 

#include "pins.h"
#include "fan.h"

//#include <util/delay.h>
//
//unsigned char crap = 0;
void HandleFan(unsigned char temperature){
	//unsigned char deltaTemp;
	
	//PORTD |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4);
	//
	//if(crap == 0){
		//PORTD &= ~(1 << LED1);
		//_delay_ms(200);
		//crap = 1;
	//}else{
		//crap = 0;
	//}
	
	//TODO: Remove
	//PORTD |= 0b00001111;
	//
	//deltaTemp = temperature / 2;
	//
	//PORTD &= ~(deltaTemp & 0b00001111);

	//if(temperature > TEMPGREEN){
		////Start fan
		//deltaTemp = temperature - TEMPGREEN;
//
		//FAN = 255 * (deltaTemp / (TEMPRED - TEMPGREEN));;
	//}else{
		//FAN = 0;
	//}
}