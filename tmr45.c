#include "tmr45.h"								//we use tmr4/5 to form a 32-bit timer

//empty handler
static void /*_tmr2_*/empty_handler(void) {
	//default tmr handler
}

static void (* /*_tmr2*/_isr_ptr)(void)=empty_handler;				//tmr5_ptr pointing to empty_handler by default

//TMR45 uses T5's interrupt
void _ISR _T5Interrupt(void) {
	_T5IF=0;									//clear tmr5 interrupt flag
	/*_tmr2*/_isr_ptr();						//execute user tmr5 isr
}

//initialize the timer4/5 (32bit)
void tmr45_init(unsigned char ps) {
	_T4MD = _T5MD = 0;							//enable power to tmr4/5
	_T4ON = _T5ON = 0;							//0->turn off tmr4/5
	/*_tmr2*/_isr_ptr=/*_tmr2_*/empty_handler;	//point to default handler
	PR4 = PR5 =/*period*/-1;					//maximum tmr period
	_T4CS = _T5CS = 0;							//0->use internal clock = Fosc / 2
	_T4_32 = 1;									//clock as one 32-bit timer/counter
	_T4CKPS=ps & TMR_PS_MASK;					//set prescaler to LSB tmr4
	_T5CKPS=TMR_PS_1x;							//set prescaler on MSB tmr5 to 1:1
	_T4GE = _T5GE = 0;							//0->gating disabled
	_T4IF = _T5IF = 0;							//0->reset the flag
	_T4IE = _T5IE = 0;							//0->disable tmr4/5 interrupts
	TMR4 = TMR5 = 0;							//reset the timer/counter
	_T4ON = _T5ON = 1;							//1->turn on tmr4/5
}

//activate the isr handler
void tmr45_act(void (*isr_ptr)(void)) {
	/*_tmr2*/_isr_ptr=isr_ptr;					//activate the isr handler
	_T4IF = _T5IF = 0;							//0->reset the flag
	_T5IE = 1;									//1->enable interrupt on the MSB timer
	_T4IE = 0;									//0->disable interrupt on the LSB timer
}
