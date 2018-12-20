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

#define num_0 (1<<a|1<<b|1<<c|1<<d|1<<e|1<<f)
#define num_1 (1<<b|1<<c)
#define num_2 (1<<a|1<<b|1<<g|1<<e|1<<d)
#define num_3 (1<<a|1<<b|1<<c|1<<d|1<<g)
#define num_4 (1<<b|1<<c|1<<f|1<<g)
#define num_5 (1<<a|1<<c|1<<d|1<<f|1<<g)
#define num_6 (1<<a|1<<c|1<<d|1<<e|1<<f|1<<g)
#define num_7 (1<<a|1<<b|1<<c)
#define num_8 (1<<a|1<<b|1<<c|1<<d|1<<e|1<<f|1<<g)
#define num_9 (1<<a|1<<b|1<<c|1<<d|1<<f|1<<g)
	
volatile uint8_t AD_T_MODE = 0;
volatile uint8_t door_is_open = 0;
volatile uint8_t RT_minutes = 0 , RT_HOURS = 0;
volatile uint8_t stop_watch_second =0 , stop_watch_minutes=0 ;

void init_oven()
{
	DDRC =0xFF; //SEVEN SEG DATA(OUT)
	DDRA =0XFF; //PERIPHRAL, SEVEN SEG ADDR(OUT)
	DDRD =0X00;	//BUTTONS (IN)
	PORTD =0XFF; //TURN ON PULUP RESISTANTS
	
	// INIT THE EXTERNAL INTRUPPT => INIT0 "any change ",INIT1 "FULLING adge" 
}

void beep(int duration)
{
	sbi(peripheral_port,bzr);
	_delay_ms(duration);
	cbi(peripheral_port,bzr);
}
void init_RTC()
{
	//initialize the timer1 to Make interrupt every one second to increemint RTC 
}
void write_to_7seg(uint8_t seg_index , uint8_t num)
{
	
}
void SYSTEM_PUSE()
{
	//TURN MOTOR OF 
	//pose stop watch timer 
	//dsplay RTC 
}
int main(void)
{
	sei();
	init_oven();
	init_RTC();
    while(1)
    {
		if (AD_T_MODE)
		{
			/*/////////////////////////////////////////////////////////////////
			if pls_ten_bn pressed => increment stop watch time
			if start_bn pressed => initialize the STOP WATCH TIMER ,START Process
			if cancel_bn pressed firist time => pause the stop watch timer
			else if presed second time => make the timer = 0 ;
			//////////////////////////////////////////////////////////////////*/
		}
		else
		{
			
		}
		
    }
}
ISR(INT1_vect)
{
	//T_Adj_Bn IS PRESSED
	AD_T_MODE = 1 ;
}

ISR(INT0_vect)
{
	//DOOR IS OPEN
	door_is_open = 1;
}