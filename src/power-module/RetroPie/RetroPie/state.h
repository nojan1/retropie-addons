/*
 * state.h
 *
 * Created: 2015-05-13 19:17:29
 *  Author: hedlundn
 */ 


#ifndef STATE_H_
#define STATE_H_


#define BOOTING 1
#define RUNNING 2
#define SHUTTING_DOWN 3
#define OFF 4

void SetState(int);
int GetState();
volatile char currentState;
#endif /* STATE_H_ */