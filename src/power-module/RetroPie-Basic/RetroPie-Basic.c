/*
 * RetroPie_Basic.c
 *
 * Created: 2016-05-12 17:53:55
 *  Author: hedlundn
 */ 

#include "pins.h"

#include <avr/io.h>
#include <util/delay.h>

const int SHORT_CLICK = 3;

int main(void)
{
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
	
	unsigned char powerbuttonDownCounter = 0;
	unsigned char isRunning = 0;
	
    while(1)
    {
        //Check power button
        powerbuttonDownCounter = 0;
        while(PINC & (1 << PWR_SWITCH))
        {
	        powerbuttonDownCounter++;
	        _delay_ms(40);
        }
		
		if(powerbuttonDownCounter >= SHORT_CLICK)
		{
			if(isRunning == 1){
				isRunning = 0;
				PORTC &= ~(1 << PWR_RELAY);
				
				PORTD |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4);
				_delay_ms(500);
			}else{
				isRunning = 1;
				PORTC |= (1 << PWR_RELAY);
				
				for(int i = 0; i < 5; i++){
					PORTD |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4);
					if(i != 0){
						_delay_ms(100);
					}
					
					PORTD &= ~((1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << LED4));
					_delay_ms(100);
				}
				
				_delay_ms(500);
			}
		}
    }
}