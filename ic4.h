#ifndef _IC4_H
#define _IC4_H

#include "gpio.h"

//hardware configuration
//end hardware configuration

//global defines
#define IC4_PIN()	PPS_IC4_TO_RP(6)	//assign input capture pin to GPIO

//global variables


//reset input capture 4
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic4_init(void);

//activate user ptr
void ic4_act(void (*isr_ptr)(void));

//read ICxBUF result
uint16_t ic4_get(void);

#endif
