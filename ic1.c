#include "ic1.h"						//we use input capture

//hardware configuration
//end hardware configuration

//global defines
#define ICxMD		PMD2bits.IC1MD
#define ICxCON		IC1CON
#define ICxIF		IFS0bits.IC1IF
#define ICxIE		IEC0bits.IC1IE
#define ICxIP		IPC1bits.IC1IP
#define ICxBUF		IC1BUF

//global variables

void empty_handler(void) {
	//do nothing here
}

static void (*_isrptr)(void)=empty_handler;				//function pointer pointing to empty_handler by default
volatile uint16_t ICxDAT;

//input capture ISR
void _ISR _IC1Interrupt(void) {			//for PIC24
	//clear the flag
	ICxDAT = ICxBUF;					//read the capture buffer first
	ICxIF = 0;							//clear the flag after the buffer has been read (the interrupt flag is persistent)
	_isrptr();							//run user handler
}

//reset input capture 1
//16-bit mode, rising edge, single capture, Timer2 as timebase
//interrupt disabled
void ic1_init(void) {
	_isrptr = empty_handler;			//reset user handler
#if defined(IC1_PIN)
	IC1_PIN();							//assign pin to IC
#endif
	ICxMD = 0;							//0->enable power to input capture
	ICxCON  = 	//(0<<15) |				//1->enable the module, 0->disable the module
				(0<<13) |				//0->operates in idle, 1->don't operate in idle
				//(1<<9) |				//1-.capture rising edge first (only used for ICM110)
				//(0<<8) |				//1->32-bit mode, 0->16-bit mode
				(1<<7) |				//1->timer2 as timebase, 0->timer3 as timebase
				(0<<5) |				//0->interrupt on every capture event, 1->on every second capture event, ...
				(0<<4) |				//0->ICx no overflow, 1->ICx overflow
				(0<<3) |				//0->buffer is empty, 1->buffer is not empty
				(3<<0) |				//0->ICx disabled, 1->every edge, 2->every falling edge, 3->every rising edge, ...
				0x00;

	//ICxBUF;							//read the buffer to clear the flag
	ICxIF   = 0;						//0->clear the flag
	ICxIE   = 0;						//1->enable the interrupt, 0->disable the interrupt
	//ICxIP   = 1;						//optional
	//enable the input capture
	ICxCON |= (1<<15);					//1->enable the module, 0->disable the module
	//input capture running now
}

//activate user ptr
void ic1_act(void (*isr_ptr)(void)) {
	_isrptr = isr_ptr;					//install user ptr
	//ICxBUF;							//read the buffer to clear the flag
	ICxIF   = 0;						//0->clear the flag
	ICxIE   = 1;						//1->enable the interrupt, 0->disable the interrupt
}

//read ICxBUF result
uint16_t ic1_get(void) {
	return ICxDAT;
}
