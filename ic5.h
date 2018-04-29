#ifndef _IC5_H
#define _IC5_H

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
#define IC5_PIN()	PPS_IC5_TO_RP(6)	//assign input capture pin to GPIO

//global variables


//reset input capture 5
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic5_init(void);

//activate user ptr
void ic5_act(void (*isr_ptr)(void));

//read ICxBUF result
uint16_t ic5_get(void);

#endif
