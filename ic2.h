#ifndef _IC2_H
#define _IC2_H

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
#define IC2_PIN()	PPS_IC2_TO_RP(6)	//assign input capture pin to GPIO

//global variables


//reset input capture 2
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic2_init(void);

//activate user ptr
void ic2_act(void (*isr_ptr)(void));

//read ICxBUF result
uint16_t ic2_get(void);

#endif
