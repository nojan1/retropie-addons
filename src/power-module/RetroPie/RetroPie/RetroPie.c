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
#include <util/delay.h>

const int SHORT_CLICK = 3;
const int LONG_CLICK = 15;
const int SHUTDOWN_WAIT = 10;

unsigned char waitCounter = 0;
unsigned char ledState = 1;

void UpdateLeds()
{
	PORTD = 0xff;
	PORTD &= ~ledState;
	
	ledState = ledState << 1;
	if(ledState > 8)
	{
		ledState = 1;
	}
}

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

	SetState(OFF);

	unsigned char powerbuttonDownCounter = 0;
	
    while(1)
    {
		//Check power button
		powerbuttonDownCounter = 0;
		while(PINC & (1 << PWR_SWITCH))
		{
			powerbuttonDownCounter++;
			_delay_ms(20);
		}
			
		if(powerbuttonDownCounter >= LONG_CLICK)
		{
			//Reset
			SetState(OFF);
			waitCounter = 0;
		}
		else if(powerbuttonDownCounter >= SHORT_CLICK)
		{
			
			switch(GetState())
			{
				case OFF:
					SetState(BOOTING);
					_delay_ms(100);
					break;
				case RUNNING:
					SetState(SHUTTING_DOWN);
					break;
			}
			
			waitCounter = 0;
		}
		
        switch(currentState)
		{
			case RUNNING:
				if( !(PINC & (1 << PIE_SENSE)))
				{
					SetState(SHUTTING_DOWN);
				}
				break;
			case BOOTING:
				UpdateLeds();
			
				if((PINC & (~(1 << PIE_SENSE))) && waitCounter > 20)
				{
					waitCounter = 0;
					SetState(RUNNING);
				}
				break;
			case SHUTTING_DOWN:
				UpdateLeds();
				waitCounter++;		

				if( !(PINC & (1 << PIE_SENSE)) && waitCounter > SHUTDOWN_WAIT)
				{
					waitCounter = 0;

					SetState(OFF);
				}

			break;	
			
		}
		
		_delay_ms(250);
    }
}