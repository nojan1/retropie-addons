/*
 * pins.h
 *
 * Created: 2015-05-13 19:24:01
 *  Author: hedlundn
 */ 

#include <avr/io.h>

#ifndef PINS_H_
#define PINS_H_

#define F_CPU 1000000UL

//Port C
#define PIE_SIGNAL 0
#define PIE_SENSE 1
#define PWR_RELAY 2
#define PWR_SWITCH 3


//PORT D
#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3

#define FAN OCR0A

#endif /* PINS_H_ */