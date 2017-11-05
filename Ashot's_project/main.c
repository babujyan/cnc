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
unsigned char	b;
unsigned int	c;
unsigned char	Nuber_of_operetions;
//unsigned char	u;
//unsigned char	manual_mode_motor_1_state;
unsigned char	manual_mode;
//unsigned char	manual_mode_motor_2_state;
//ISR (INT0_vect)
//{
	//PORTB|=(1<< PB0);
//
	//while(PIND3==0)
	//{	
		//PORTB^=(1<< PB1 );
		//_delay_ms(100);
	//}
//
	//PORTB&=(0<< PB0);
//}

ISR (INT0_vect)
{	
	if(AUTOMATIC_state==ON)
	{
		battom1=ON;
		j1=0;
		c=40960;//2560;
	}
}

ISR (TIMER2_COMPA_vect) 
{
	
	if(battom1==ON)
	{
		AUTOMATIC_state=OFF;

		//PORTB|=(1<< PB0);
		motor_1_ON;

		if (b!=0)
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

				if(c!=5)
				{
				c=c/2;
				j1=c; 
				}
				else
				j1=4;//1khz generation 6sc 10-200ms wait 

				/*==== >> avelacrac masi verj << ====*/
				/*************************************/

			}

			else
			{
				j1--;
			}

			if(i1==12000)
			{
				i1=0;
				b--;
				
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
			PORTB|=0x04;//(1<< PB2);
			//PORTB&=0xFE;//(0<< PB0);
			motor_1_OFF;
			battom1=OFF;
			battom0=ON;
			j0=0;
			//b=Nuber_of_operetions;
			b=4;
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
			i0++;
			j0=50;
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
		}
	
	}


}

//ISR (ADC_vect)
//{
	//unsigned temp;
//
	//ADC_value  = ADCL;
	//temp = ADCH;
	//ADC_value |= (temp<<8);
	////if(){}
//}



/***************************************
===========>> manual mode <<===========*/
/*======= >> avelacrac mas << ==========*/

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

	PORTB^=0x20;

	//manual_mode=0x08 & PORTD;
	manual_mode_check;
	while(manual_mode==ON)//)PD3
	{
		
		while(manual_mode_motor_1_on_check!=OFF)//PIND4==0x10 check if the flag is on
		{ 
			//PORTB|=0x01;
			motor_1_ON;
			//PORTB^=0x02;//(1<< PB1 );
			motor_1_Inverse;
			_delay_us(500);
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
				_delay_ms(5);
			}

			
		}
		//PORTD&=0x7F;
		motor_2_OFF;
		motor_2_signal_OFF;

		manual_mode_check;
	}
	AUTOMATIC_state=ON;


}
/*==== >> avelacrac masi verj << ====*/
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

	b=4;

	AUTOMATIC_state=ON;

	sbi(motor_1_freq_DDR,motor_1_freq_DDR_pin);
	sbi(motor_1_ON_OFF_DDR,motor_1_ON_OFF_DDR_pin);
	sbi(motor_1_dir_DDR,motor_1_dir_DDR_pin);
	//DDRB=(1<<DDB1)|(1<<DDB0)|(1<<DDB2)|(1<<DDB5);
	//PORTB=(1<< PB2)|(1<<PB5);
	motor_1_dir_on;
	PORTD=0x00;
	DDRD=(1<<DDD7)|(1<<DDD6);
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