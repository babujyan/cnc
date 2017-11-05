#ifndef DEFINES
	#define DEFINES

	#define F_CPU 16000000UL
	#define BAUD 9600UL
	#define MY_UBRR (F_CPU/16/BAUD-1)

	#define ON 0x01
	#define OFF 0x00

	#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
	#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
	/*--------------motor 1 pin setup-----------*/
	#define motor_1_freq_DDR				DDRB
	#define motor_1_ON_OFF_DDR				DDRB
	#define motor_1_dir_DDR					DDRB

	#define motor_1_freq_DDR_pin			DDB5//1-->5
	#define motor_1_ON_OFF_DDR_pin			DDB3//0-->3
	#define motor_1_dir_DDR_pin				DDB4//2-->4

	#define motor_1_freq_PORT				PORTB 
	#define motor_1_ON_OFF_PORT				PORTB
	#define motor_1_dir_PORT				PORTB

	#define motor_1_freq_pin				PB5//digital 13
	#define motor_1_ON_OFF_pin				PB3//digital 11
	#define motor_1_dir_pin					PB4//digital 12
	/*--------------motor 1-----------*/
	#define motor_1_Inverse					motor_1_freq_PORT^=(1<< motor_1_freq_pin )//digital 9
	#define motor_1_signal_OFF				cbi(motor_1_freq_PORT,motor_1_freq_pin)//shpindeli motor
	#define motor_1_ON						sbi(motor_1_ON_OFF_PORT,motor_1_ON_OFF_pin)//digital 8
	#define motor_1_OFF						cbi(motor_1_ON_OFF_PORT,motor_1_ON_OFF_pin)//motori razrisheni
	#define motor_1_dir_on					sbi(motor_1_dir_PORT,motor_1_dir_pin)//digital 10
	#define motor_1_dir_inverse				motor_1_dir_PORT^=(1<< motor_1_dir_pin)
	/*--------------motor 2 pin setup-----------*/
	#define motor_2_freq_DDR				DDRB
	#define motor_2_ON_OFF_DDR				DDRB
				  
	#define motor_2_freq_DDR_pin			DDB0
	#define motor_2_ON_OFF_DDR_pin			DDB1

	#define motor_2_freq_PORT				PORTB
	#define motor_2_ON_OFF_PORT				PORTB
				  
	#define motor_2_freq_pin				PB0//digital 8
	#define motor_2_ON_OFF_pin				PB1//digital 9
	
	/*--------------motor 2-----------*/
	#define motor_2_Inverse					motor_2_freq_PORT^=(1<< motor_2_freq_pin)//digital 8
	#define motor_2_signal_OFF				cbi(motor_2_freq_PORT,motor_2_freq_pin)
	#define motor_2_ON						sbi(motor_2_ON_OFF_PORT,motor_2_ON_OFF_pin)//digital 9
	#define motor_2_OFF						cbi(motor_2_ON_OFF_PORT,motor_2_ON_OFF_pin)

	#define manual_mode_check				(0x08 & PIND)//PD2 digital 2
	#define manual_mode_motor_1_on_check	(0x10 & PIND)//PD4 digital 4 check

	#define manual_mode_motor_2_on_check	(0x04 & PINB)//PB2 digital 10 check
	
	/*--------------led---------------*/
	#define led_check						(0x40 & PIND)//6 pd6 
	#define auto_correct_check				(0x80 & PIND)//7 pd7 
	

	#define shpindel_path_counter_VAR		2//
	#define motor_1_hz						1000 // hz anpayman zuyg 
	#define motor_1_code_hz					((10000/(motor_1_hz*2))-1)
	
	#define motor_2_hz						100  //hz  anpayman 20 bajanvox 
	#define motor_2_code_hz					((10000/(motor_2_hz*2))-1)
	#define time_sec						6 //seconds 
	#define motor_1_work_time				2*time_sec*motor_1_hz
#endif //DEFINES