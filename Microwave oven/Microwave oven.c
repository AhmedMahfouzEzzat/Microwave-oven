/*
 * Microwave_oven.c
 *
 * Created: 14/12/2018 09:04:24 م
 *  Author: AHMED
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "MCT617.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#define peripheral_port PORTA
#define Oven_indicator_led 4
#define T_Adj_indicator_led 5
#define bzr 6
#define twist_motor 7

#define button_port PORTD
#define start_bn 0
#define cancel_bn 1
#define scroll_bn 0
#define done_bn 1
#define door_switch 2
#define T_Adj_Bn 3
#define pls_one_bn 4
#define pls_ten_bn 4

#define seven_seg_data_port PORTC
#define a 0
#define b 1
#define c 2
#define d 3
#define e 4
#define f 5
#define g 6
#define dp 7

#define seven_seg_addr_port PORTA
#define s1 0
#define s2 1
#define s3 2
#define s4 3

#define sbi(port,bit) (port) |= (1 << (bit)) 
#define cbi(port,bit) (port) &= ~(1 << (bit)) 

#define beep() (peripheral_port^= (1<<bzr)) 

#define num_0 ~(1<<a|1<<b|1<<c|1<<d|1<<e|1<<f)
#define num_1 ~(1<<b|1<<c)
#define num_2 ~(1<<a|1<<b|1<<g|1<<e|1<<d)
#define num_3 ~(1<<a|1<<b|1<<c|1<<d|1<<g)
#define num_4 ~(1<<b|1<<c|1<<f|1<<g)
#define num_5 ~(1<<a|1<<c|1<<d|1<<f|1<<g)
#define num_6 ~(1<<a|1<<c|1<<d|1<<e|1<<f|1<<g)
#define num_7 ~(1<<a|1<<b|1<<c)
#define num_8 ~(1<<a|1<<b|1<<c|1<<d|1<<e|1<<f|1<<g)
#define num_9 ~(1<<a|1<<b|1<<c|1<<d|1<<f|1<<g)


#define beep (peripheral_port^= (1<<bzr)) 

volatile uint8_t AD_T_MODE = 0 , door_is_open = 0 ;
<<<<<<< HEAD
volatile uint8_t RT_second = 0 , RT_minutes = 0 , RT_HOURS = 0;
=======
volatile uint8_t RT_minutes = 0 , RT_HOURS = 0,,RT_seconds =0;
>>>>>>> 74d8a00af0222f5921954be487797f181ab3223d
volatile uint8_t stop_watch_second =0 , stop_watch_minutes=0 ;
enum PROCESS{RUN , PUSED , END , NONE};

enum PROCESS MY_PROCESS ;

void init_oven()
{
	DDRC =0xFF; //SEVEN SEG DATA(OUT)
	DDRA =0XFF; //PERIPHRAL, SEVEN SEG ADDR(OUT)
	DDRD =0X00;	//BUTTONS (IN)
	PORTD =0XFF; //TURN ON PULUP RESISTANTS
	
	MY_PROCESS =NONE ;
	
	// INIT THE EXTERNAL INTRUPPT => INIT0 "any change ",INIT1 "FULLING adge" 
	MCUCR |= (1<<ISC00)|(1<<ISC11);
	GICR |= (1<<INT0)|(1<<INT1);
	
}
void INIT_RTC()
{
	
	sbi( TIMSK ,TOIE1);
}

void INC_RTC()
{
	if (RT_seconds == 60)
        RT_minutes++;
    if(RT_minutes ==60)
	   RT_HOURS++;
	
}

void INC_SW()
{
	if (stop_watch_second ==60)
	    stop_watch_minutes++;
	
}
void DEC_SW()
{
	int count=0;
	while ((stop_watch_minutes*60)--)
	{
		 count++;
	if (count ==60)
	{
		 stop_watch_minutes--;
	}
	}
}

//display 2 digit
void display_2_digit(uint8_t num ,uint8_t seg1,uint8_t seg2)
{
	uint8_t nums[] ={num_0,num_1,num_2,num_3,num_4,num_5,num_6,num_7,num_8,num_9};
	sbi(seven_seg_addr_port , seg2);
	seven_seg_data_port =nums[(num %10)];
	if(seg2 == s2)  cbi(seven_seg_data_port,dp); 	
	_delay_ms(10);
	cbi(seven_seg_addr_port , seg2);
	num/=10;
	sbi(seven_seg_addr_port , seg1);
	seven_seg_data_port =nums[(num %10)];
	_delay_ms(10);
	cbi(seven_seg_addr_port , seg1);
	
}

void display_rtc()
{
	display_2_digit(RT_HOURS,s1,s2);
	display_2_digit(RT_minutes,s3,s4);
}

void display_sw()
{
	display_2_digit(stop_watch_minutes,s1,s2);
	display_2_digit(stop_watch_second,s3,s4);
}
void END_PROCESS()
{
	//turn off Oven_indicator_led 
	cbi(peripheral_port,Oven_indicator_led);
	//turn off twist_motor
	cbi(peripheral_port,twist_motor);
	//	chang state of procces
	MY_PROCESS=END;
}

void START_PROCESS()
{
	
	//turn on Oven_indicator_led 
	sbi(peripheral_port,Oven_indicator_led);
	//turn on twist_motor
	sbi(peripheral_port,twist_motor);	
	//chang state of procces
	MY_PROCESS =RUN;
	

}

void SYSTEM_PUSE()
{
	//TURN MOTOR OF 
	cbi(peripheral_port,twist_motor);	
	//pose stop watch timer
	MY_PROCESS = PUSED;
}
int main(void)
{
	sei();
	init_oven();
	INIT_RTC();
	
	
    while(1)
    {
		
		/*if (AD_T_MODE)
		{
			/////////////////////////////////////////////////////////////////
			if pls_ten_bn pressed => increment stop watch time
			if start_bn pressed => initialize the STOP WATCH TIMER ,START Process
			if cancel_bn pressed firist time => pause the stop watch timer
			else if presed second time => make the timer = 0 ;
			//////////////////////////////////////////////////////////////////
		}
		else
		{
			
		}
		*/
    }
}
ISR(INT1_vect)
{
	//T_Adj_Bn IS PRESSED
	AD_T_MODE = 1 ;
}

ISR(INT0_vect)
{
	/*
	DOOR IS OPEN or CLOSED 
	toggle  state of door
	door_is_open = ! door_is_open;
	if PROCESS END => chang stat to NONE
	*/
}

ISR(TIMER1_OVF_vect)
{
	/*
	INC_RTC
	if PROCESS RUN => DEC_SW 
	if PROCESS END => beep
	*/
}