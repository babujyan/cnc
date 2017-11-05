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
unsigned char	a;
unsigned char	b;
unsigned int	c;
unsigned char	Nuber_of_operetions;
unsigned char	u;
unsigned char	w;
unsigned char	e;
unsigned char	r;
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
	if(a==ON)
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
		a=OFF;

		PORTB|=(1<< PB0);
		

		if (b!=0)
		{
			if(j1==0)
			{
				PORTB^=(1<< PB1 );
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
				
				PORTB &= 0xFC; //&=(0<< PB1);
			//	PORTB &=(0<< PB0);
				PORTB ^=0x04;//(1<< PB2);
				_delay_ms(100);
				PORTB|=0x01;//(1<< PB0);
				
			}
		}

		else
		{
			PORTB|=0x04;//(1<< PB2);
			PORTB&=0xFE;//(0<< PB0);
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
		PORTD|=(1<< PD7);

		if(j0==0)
		{
			PORTD^=(1<< PD6 );
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
			PORTD&=(0<< PD7);
			PORTD^=(0<< PD6);
			a=ON;
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
	
	
	u= 0x00;
	a=OFF;
	battom1=OFF;
	battom0=OFF;
	PORTD&=0x7F;
	PORTB&=0xFE;
	PORTB^=0x20;

	e=0x08 & PORTD;
	while(e==0)//)PD3
	{

		w= 0x10 & PIND;
		while(w!=0)//PIND4==0x10
		{ 
			PORTB|=0x01;

			PORTB^=0x02;//(1<< PB1 );
			_delay_us(500);
							
		}
			
		PORTB&=0xFE;//(0<< PB0);
		r=0x20 & PIND;
		while(r!=0)
		{
			for(u=1;u<=200;u++)
			{
				PORTD|=0x80;//(1<< PD7);
				PORTD^=0x40;//(1<< PD6 );
				_delay_ms(5);
			}

		}
		PORTD&=0x7F;
		

		}
	a=ON;


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

	a=ON;



	DDRB=(1<<DDB1)|(1<<DDB0)|(1<<DDB2)|(1<<DDB5);
	PORTB=(1<< PB2)|(1<<PB5);

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