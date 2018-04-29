#include "tmr23.h"						//we use tmr2/3 to form a 32-bit timer

//empty handler
static void /*_tmr2_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr2*/_isr_ptr)(void)=empty_handler;				//tmr3_ptr pointing to empty_handler by default

//TMR23 uses T3's interrupt
void _ISR _T3Interrupt(void) {
	_T3IF=0;									//clear tmr3 interrupt flag
	/*_tmr2*/_isr_ptr();						//execute user tmr1 isr
}

//initialize the timer1 (16bit)
void tmr23_init(unsigned char ps) {
	_T2MD = _T3MD = 0;							//0->enable power to tmr
	_T2ON = _T3ON = 0;							//0->turn off tmr
	/*_tmr2*/_isr_ptr=/*_tmr2_*/empty_handler;	//point to default handler
	PR2 = PR3 =/*period*/-1;					//tmr periods set to the max
	_T2CS = _T3CS = 0;							//0->use internal clock = Fosc / 2
	_T2_32 = 1;									//clock as one 32-bit timer/counter
	_T2CKPS=ps & TMR_PS_MASK;					//set LSB prescaler to user specification
	_T3CKPS=TMR_PS_1x;							//set MSB prescaler to 1:1
	_T2GE = _T3GE = 0;							//0->tmr gate disabled
	_T2IF = _T3IF = 0;							//0->reset the flag
	_T2IE = _T3IE = 0;							//0->tmr interrupt off
	TMR2 = TMR3 = 0;							//reset the timer/counter
	_T2ON = _T3ON = 1;							//1->turn on tmr
}

//activate the isr handler
void tmr23_act(void (*isr_ptr)(void)) {
	/*_tmr2*/_isr_ptr=isr_ptr;					//activate the isr handler
	_T2IF = _T3IF = 0;							//reset the flag
	_T3IE = 1;									//1->enable interrupt on MSB tmr
	_T2IE = 0;									//0->disable interrupt on LSB tmr
}
