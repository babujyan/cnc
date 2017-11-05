#ifndef DEFINES

	#define DEFINES

	#define F_CPU 16000000UL
	#define BAUD 9600UL
	#define MY_UBRR (F_CPU/16/BAUD-1)

	#define ON 0x01
	#define OFF 0x00

	#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
	#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
	/*--------------motor 1-----------*/
	#define motor_1_Inverse PORTB^=(1<< PB1 )//digital 9
	#define motor_1_signal_OFF cbi(PORTB,PB1)//shpindeli motor
	#define motor_1_ON sbi(PORTB,PB0)//digital 8
	#define motor_1_OFF cbi(PORTB,PB0)//motori razrisheni
	#define motor_1_dir_on sbi(PORTB,PB2)//digital 10
	#define motor_1_dir_inverse PORTB^=(1<< PB2)

	/*--------------motor 2-----------*/
	#define motor_2_Inverse PORTD^=(1<< PD6)//digital 6
	#define motor_2_signal_OFF cbi(PORTD,PD6)
	#define motor_2_ON sbi(PORTD,PD7)//digital 7
	#define motor_2_OFF cbi(PORTD,PD7)

	#define manual_mode_check (!(manual_mode=PD2 || PORTD))//PD2 digital 2
	#define manual_mode_motor_1_on_check ((0x10 & PIND))//PD4 digital 4 check

	#define manual_mode_motor_2_on_check ((0x20 & PIND))//PD5 digital 5 check

#endif //DEFINES