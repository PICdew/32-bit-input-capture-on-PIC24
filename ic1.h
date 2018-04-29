#ifndef _IC1_H
#define _IC1_H

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
#define IC1_PIN()	PPS_IC1_TO_RP(6)	//assign input capture pin to GPIO

//global variables


//reset input capture 1
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic1_init(void);

//activate user ptr
void ic1_act(void (*isr_ptr)(void));

//read ICxBUF result
uint16_t ic1_get(void);

#endif
