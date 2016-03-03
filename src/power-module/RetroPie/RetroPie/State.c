/*
 * State.c
 *
 * Created: 2015-05-13 19:15:52
 *  Author: hedlundn
 */ 

#include "state.h"
#include "pins.h"
#include <avr/io.h>
#include <util/delay.h>

volatile char currentState = 0;

void SetState(int state){
	currentState = state;
	switch(state) {
		case BOOTING:
			//Pull relay
			PORTC |= (1 << PWR_RELAY);
			//Set PIE Signal high
			PORTC |= (1 << PIE_SIGNAL);
		break;
		case RUNNING:
			//All leds on
			PORTD &= ~((1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4));
		break;
		case SHUTTING_DOWN:
			//Signal PIE to shutdown
			PORTC &= ~(1 << PIE_SIGNAL);
		break;
		case OFF:
			PORTC &= ~(1 << PWR_RELAY);
			PORTD |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4);
			//TODO: Stop Fan
		break;
	}
}

int GetState(){
	return currentState;
}