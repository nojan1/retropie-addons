/*
 * RetroPie.c
 *
 * Created: 2015-05-13 17:46:14
 *  Author: hedlundn
 */ 


#include "pins.h"
#include "state.h"
#include "fan.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char waitCounter = 0;

ISR (ADC_vect) 
{
	//ADC Conversion completed - temp reading in ADCL
	HandleFan(ADCL);
}

ISR (PCINT1_vect)
{
	cli();
	//PWR Switch or raspberry pie sense
	_delay_ms(50);

	if( PINC & (1 << PWR_SWITCH) ){
		//PWR Switch clicked
		switch(GetState()){
			case OFF:
				SetState(BOOTING);
				_delay_ms(100);
			break;
			case RUNNING:
				SetState(SHUTTING_DOWN);
			break;
		}
		
		return;
	}
	
	//PIE_SENSE went high
	if((PINC & (~(1 << PIE_SENSE))) && waitCounter > 20 && GetState() == BOOTING){
		waitCounter = 0;
		SetState(RUNNING);
	}
	
	////PIE_SENSE went low
	//if( !(PINC & (~(1 << PIE_SENSE))) && waitCounter > 10 && GetState() == SHUTTING_DOWN){
		//waitCounter = 0;
		////Raspberry switched off
		//SetState(OFF);
	//}
	
	sei();
}

int main(void)
{
	//Select channel 4
	ADMUX |= (1 << MUX2);
	//Enable ADC, Start Conversion, Enable interrupt, Prescale = 64
	ADCSRA = 0b11101110;
	//Set free running ADC	
	ADCSRB |= (0 << 3);

	//Fast PWM mode, set OC0A at bottom clear at match, Prescale = 64
	TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << WGM02) | (1 << CS01) | (1 << CS00);

	//Data pins	
	DDRC = (1 << PIE_SIGNAL) |
			(0 << PIE_SENSE) |
			(1 << PWR_RELAY) |
			(0 << PWR_SWITCH);
	
	//Port D = Output
	DDRD = 0xff;
	
	//Turn of LED's
	//PORTD |= (0b1111 << LED1);
	PORTD = 0xff;
	
	//Enable PCINT[14:8] interrupt
	PCICR |= (1 << PCIE1);
	//Enable for PCINT9 and 11
	PCMSK1 |= (1 << PCINT11) | (1 << PCINT9);

	
	SetState(OFF);
	
	sei();	
	
	unsigned char ledState = 1;
	
    while(1)
    {
        switch(currentState){
			case BOOTING:
			case SHUTTING_DOWN:
				PORTD = 0xff;
				PORTD &= ~ledState;
			
				ledState = ledState << 1;
				if(ledState > 8){
					ledState = 1;
				}
			
				_delay_ms(250);
				
				waitCounter++;

				//Check if PIE_Sense is low
				if( !(PINC & (1 << PIE_SENSE)) && waitCounter > 10 && GetState() == SHUTTING_DOWN){
					waitCounter = 0;
					//Raspberry switched off
					SetState(OFF);
				}

			break;	
			
		}
	
    }
}