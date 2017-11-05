#include "defines.h"
#include "functions.h"

#include <avr/io.h>


void 	Init_Timers()
{
	// enable timer interrupt for Timer0
		
	TCCR0A = (1<<WGM21); //ctc
	TCCR0B = (1<<CS01);   //use clk/8
	TIMSK0 = (1<<OCIE0A); //interrupt
	TCNT0=0x00;
	OCR0A=199;   // 10kHz


	//// enable timer interrupt for Timer1
//
	//TCCR1B=(1<<WGM12)|(1<<CS11); //use clk/8
	//TCCR1C=(1<<FOC1A);
	//TIMSK1=(1<<OCIE1A);
	//TIFR1=(1<<OCF1A);
	//TCNT1H=0x00;
	//TCNT1L=0x00;
	//OCR1A=199;	// 10kHz


	// enable timer interrupt for Timer2

	TCCR2A = (1<<WGM21); //ctc
	TCCR2B = (1<<CS21);   //use clk/8
	TIMSK2 = (1<<OCIE2A); //interrupt
	TCNT2=0x00;
	OCR2A=199;   // 10kHz

}

void Init_Interrupts()
{
	// enable External Interrupt Request 0 (pin 2)

	EICRA =0x03; //(1<<ISC00) | (1<<ISC01);
	//EIMSK = (1<<INT0);
	//EIFR = (1<<INTF0);
//
	//// enable External Interrupt Request 1 (pin 3)

	//EICRA =0x00;//(1<<ISC10) | (1<<ISC11);
	EIMSK = 0x03;//(1<<INT1);
	EIFR = 0x03;//(1<<INTF1);
//
	// enable Pin Change Interrupts 5,4,3.
	//PCICR=(1<<PCIE0);
	//PCIFR=(1<<PCIF0);
	//PCMSK0=(1<<PCINT5)|(1<<PCINT3)|(1<<PCINT2);

}

//void Init_ADC()
//{
	//
	//ADMUX  = (1<<REFS0);//ADC0 with AVCC with external capacitor at AREF pin
	//ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)| (1<<ADATE); //ADATE ADC Auto Trigger Enable
	//ADCSRB = (1<<ADTS0) | (1<<ADTS2);//Timer/Counter1 Compare Match B
	//DIDR0 = 0x3E;
//}
//
//unsigned int ADC_read()
//{
	////while(ADCSRA & (1<<ADSC));
	//return ADC;
//}