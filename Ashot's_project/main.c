/*
 * Ashot's_project.c
 *
 * Created: 06.08.2017 14:32:17
 * Author : Hrach
 */ 
#include "defines.h"
#include "functions.h"
#include "functions.cpp"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int	ADC_value;
unsigned int	battom0;
unsigned int	i0;
unsigned int	j0;
unsigned int 	battom1;
unsigned int 	i1;
unsigned int 	j1;
unsigned char	AUTOMATIC_state;//lets automatic mode to start
unsigned char	shpindel_path_counter;
unsigned int	c;
unsigned char	Nuber_of_operetions;
uint8_t			auto_correct;
uint8_t			led;
unsigned char	manual_mode;
uint8_t			motor_2_counter_checker = 0;

ISR (INT0_vect)
{	
	if(AUTOMATIC_state==ON)
	{
		battom1=ON;
		j1=0;
		//c=40960;//2560;
	}
}

ISR (TIMER2_COMPA_vect) 
{
	
	if(battom1==ON)
	{
		AUTOMATIC_state=OFF;
		motor_1_ON;

		if (shpindel_path_counter!=0)
		{
			if(j1==0)
			{
				motor_1_Inverse;
				i1++;

				/*************/
				// hin code 

			//	j1=4;

				/*******************************/
				/*==== >> avelacrac mas << ====*/
//
				//if(c!=5)
				//{
				//c=c/2;
				//j1=c; 
				//}
				//else

				j1=motor_1_code_hz;//1khz generation 6sc 10-200ms wait 

				/*==== >> avelacrac masi verj << ====*/
				/*************************************/

			}

			else
			{
				j1--;
			}

			if(i1==motor_1_work_time)
			{
				i1=0;
				shpindel_path_counter--;
				
				//PORTB &= 0xFC; //&=(0<< PB1);
				motor_1_signal_OFF;
				//PORTB &=(0<< PB0);
				motor_1_OFF;
				//PORTB ^=0x04;//(1<< PB2);
				motor_1_dir_inverse;
				_delay_ms(100);



				//PORTB|=0x01;//(1<< PB0);
				motor_1_ON;
			}
		}

		else
		{
			//PORTB|=0x04;//(1<< PB2);//////////////////////////////////////////
			motor_1_dir_on;
			//PORTB&=0xFE;//(0<< PB0);
			motor_1_OFF;
			battom1=OFF;
			battom0=ON;
			j0=0;
			//b=Nuber_of_operetions;
			shpindel_path_counter=shpindel_path_counter_VAR;
		}
	}

}	



ISR (TIMER0_COMPA_vect)
{
	if(battom0==ON)
	{
		//PORTD|=(1<< PD7);
		motor_2_ON;
		if(j0==0)
		{
			//PORTD^=(1<< PD6 );
			motor_2_Inverse;
			j0=motor_2_code_hz;

			i0++;
			}

		else
		{
			j0--;
		}
		if(i0==200)
		{
			i0=0;
			battom0=OFF;
			
			//PORTD&=(0<< PD7);
			motor_2_OFF; 
			//PORTD^=(0<< PD6);
			//motor_2_Inverse;
			motor_2_signal_OFF;
			AUTOMATIC_state=ON;
			battom1=ON;
			j1=0;
			motor_2_counter_checker++;
		}

			if (motor_2_counter_checker == 2)
			{
				led = led_check; //6 pd6 // pinb3 pin 11

				while(led==OFF)
				{
					//PORTB|=0x02;  //  9 pb1 (1<< PB1 ) // PORTD|=0x80;//(1<< PD7);
					//PORTB^=0x01;  // 8 pb0 (1<< PB0 ) // PORTD^=0x40;//(1<< PD6
					motor_2_ON;
					motor_2_Inverse;
					_delay_ms(motor_2_hz/20);
					led = led_check; // 6 pd6 // pinb3 pin
				}
				//PORTB&=0x6B; // 8 pb0 - 11 pb3 // 9 pb1 - 13 pb5 // 1111 1100 <<----petqa poxel
				motor_2_OFF;
				motor_2_signal_OFF;
				motor_2_counter_checker = 0;
			}
	}
}


/***************************************
===========>> manual mode <<===========*/
ISR(INT1_vect)
{
	//u= 0x00;
	AUTOMATIC_state=OFF;
	battom1=OFF;
	battom0=OFF;
	//PORTD&=0x7F;
	motor_2_signal_OFF;
	motor_2_OFF;
	//PORTB&=0xFE;
	motor_1_OFF;
	motor_1_dir_on;
	motor_1_dir_inverse;

	//manual_mode=0x08 & PORTD;
	manual_mode=manual_mode_check;
	while(manual_mode_check==OFF)//)PD3//inverse logic should be ==ON
	{
		
		while(manual_mode_motor_1_on_check!=OFF)//PIND4==0x10 check if the flag is on
		{ 
			//PORTB|=0x01;
			motor_1_ON;
			//PORTB^=0x02;//(1<< PB1 );
			motor_1_Inverse;
			_delay_us(motor_1_hz/2);
			//w= 0x10 & PIND;				
		}
			
		//PORTB&=0xFE;//(0<< PB0);
		motor_1_OFF;
		motor_1_signal_OFF;

		
		while(manual_mode_motor_2_on_check!=OFF)
		{
			for(uint8_t u=1;u<=200;u++)
			{
				//PORTD|=0x80;//(1<< PD7);
				//PORTD^=0x40;//(1<< PD6 );
				motor_2_ON;
				motor_2_Inverse;
				_delay_ms(motor_2_hz/20);
			}

			
		}
		//PORTD&=0x7F;
		motor_2_OFF;
		motor_2_signal_OFF;

		auto_correct = auto_correct_check;// 7 pd7 // pinb4 pin 12
		while(auto_correct!=OFF)
		{
			led = led_check; //6 pd6 // pinb3 pin 11

			while(led==OFF)
			{
				//PORTB|=0x02;  //  9 pb1 (1<< PB1 ) // PORTD|=0x80;//(1<< PD7);
				//PORTB^=0x01;  // 8 pb0 (1<< PB0 ) // PORTD^=0x40;//(1<< PD6 
				motor_2_ON;
				motor_2_Inverse;
				_delay_ms(motor_2_hz/20);
				led = led_check; // 6 pd6 // pinb3 pin 
			}
			//PORTB&=0x6B; // 8 pb0 - 11 pb3 // 9 pb1 - 13 pb5 // 1111 1100 <<----petqa poxel
			motor_2_OFF;
			motor_2_signal_OFF;
			auto_correct = auto_correct_check; //12 pb4 --> 7 pd7 // pinb4 pin 12
		}
	}
	AUTOMATIC_state=ON;
}

/********************************/


int main(void)
{
	//way=0x00;
	battom0=OFF;
	i0=0;
	j0=0;
	battom1=OFF;
	i1=0;
	j1=0;

	shpindel_path_counter=shpindel_path_counter_VAR;

	AUTOMATIC_state=ON;
	PORTB=0x00;
	PORTD=0x00;
	DDRB=0x00;
	DDRD=0x00;

	sbi(motor_1_freq_DDR,motor_1_freq_DDR_pin);
	sbi(motor_1_ON_OFF_DDR,motor_1_ON_OFF_DDR_pin);
	sbi(motor_1_dir_DDR,motor_1_dir_DDR_pin);
	//DDRB=(1<<DDB1)|(1<<DDB0)|(1<<DDB2)|(1<<DDB5);
	//PORTB=(1<< PB2)|(1<<PB5);
	motor_1_dir_on;
	motor_2_freq_PORT=0x00;//bla bla bla pull up stuff
	sbi(motor_2_freq_DDR,motor_2_freq_DDR_pin);
	sbi(motor_2_ON_OFF_DDR,motor_2_ON_OFF_DDR_pin);
	//PORTD=(1<<PORTD3);
	

	cli();
	Init_Interrupts();
	Init_Timers();
	//Init_ADC();
	//ADC_read();
	sei();

	//Nuber_of_operetions=PIND&0x1C;
	//Nuber_of_operetions=(Nuber_of_operetions>>2);
	//b=Nuber_of_operetions;

	while(1)
	{
		_delay_ms(1000);
	}
	
	//Nuber_of_operetions=PIND&0x1C;
	//Nuber_of_operetions=(Nuber_of_operetions>>2);
}