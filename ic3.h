#ifndef _IC3_H
#define _IC3_H

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
#define IC3_PIN()	PPS_IC3_TO_RP(6)	//assign input capture pin to GPIO

//global variables


//reset input capture 3
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic3_init(void);

//activate user ptr
void ic3_act(void (*isr_ptr)(void));

//read ICxBUF result
uint16_t ic3_get(void);

#endif
