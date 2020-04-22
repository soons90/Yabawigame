/*
 * timer.c
 *
 * Created: 2019-09-19 오전 11:38:44
 *  Author: 정경윤
 */ 
#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"


extern volatile char FND_font[10];
extern volatile char FND_digit[4];
extern volatile char FND[4];

//extern volatile char SFND_font[10];
//extern volatile char SFND_digit[4];
//extern volatile char SFND[4];


ISR(TIMER0_COMPA_vect){
	if(sw_start_flag)sw_msec++;
	if(sw_msec >= 1000){
		sw_msec = 0;
		sw_sec++;
		//PORTB ^= 1 << PORTB5;
		if(sw_sec >= 60){
			sw_sec = 0;
			sw_min++;
			if(sw_min >= 60){
				sw_min = 0;
			}
		}
	}
	if(sw_msec%100 == 0)time_print_flag = 1;
	msec++;
	if(msec >= 1000){
		msec = 0;
		sec++;
		//PORTB ^= 1 << PORTB5;
		if(sec >= 60){
			sec = 0;
			min++;
			if(min >= 60){
				min = 0;
			}
		}
	}
	//if(msec%100 == 0)time_print_flag = 1;
	
 	/*FND4digit_com_PORT |= 0b00111100;
 	FND4digit_data_PORT = FND[msec%4];
 	FND4digit_com_PORT &= FND_digit[msec%4];*/
	
	/*SHIFT_REGISTER_FND_COM_PORT |= 1 << DIGIT_1 | 1 << DIGIT_10 |1 << DIGIT_100 |1 << DIGIT_1000;
	shift_register_send_byte(SFND[msec%4]);
	SHIFT_REGISTER_FND_COM_PORT &= SFND_digit[msec%4];  */
}

void timer_main(void){
	char up_down_flag = 1;
	//FND4digit_init();
	//timer0_compA_msec_int_init();
	//timer1_fast_PWM_init();
	//timer1_fast_PWM_survo_motor_init();
	//timer2_fast_PWM_init();
	sei();
	//TCNT1 = TCNT2;
	OCR2B = 1;
	OCR1A = 30;
	while(1){
		timer1_CTC_outA_speaker_init();
		OCR1A++;
		if(OCR1A >= 170){
			OCR1A = 30;
		}
		/*if(time_print_flag){
			time_print_flag = 0;
			FND_update_time(min, sec, msec);
		}*/
		/*if(up_down_flag){
			OCR2B++;
			if(OCR2B >= 150)up_down_flag = 0;
		}
		else {
			OCR2B--;
			if(OCR2B <= 1)up_down_flag = 1;
		}*/
		/*OCR1A += 1;
		if(OCR1A >= 160)OCR1A = 30;
		OCR1B += 2;
		if(OCR1B >= 160)OCR1B = 30;
		OCR2A += 1;
		if(OCR2A >= 160){
			OCR2A = 30;
			TCNT2 = 0;
		}*/
		//FND_update(OCR1A);
		_delay_ms(50);
	}
}
void timer0_compA_msec_int_init(void){	//1msec 주기 인터럽트
	TCCR0A |= 1 << WGM01;				//CTC mode
	TCCR0B |= 1 << CS00 | 1 << CS01;	//64분주
	OCR0A = 249;						//1msec 주기
	TIMSK0 |= 1 << OCIE0A;				//인터럽트 활성화		
	return;
}
void timer1_fast_PWM_init(void){
	DDRB |= 1 << PORTB1 | 1 << PORTB2;
	TCCR1A |= 1 << COM1A1 | 1 << COM1B1 | 1 << WGM11;
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS10;
	OCR1A = 0;
	OCR1B = 0;
	ICR1 = 240;
	return;
}
void timer2_fast_PWM_init(void){
	DDRD |= 1 << PORTD3;
	TCCR2A |= 1 << COM2B1 | 1 << WGM20 | 1 << WGM21;
	TCCR2B |= 1 << CS20;
	OCR2B = 0;
	return;
}
/*
survo motor SG90
OCR 30 => 5도
OCR 160 => 170도
*/
void timer1_fast_PWM_survo_motor_init(void){  
	DDRB |= 1 << PORTB1;
	TCCR1A |= 1 << COM1A1 | 1 << WGM11;
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS12;
	//OCR1A = 30;
	ICR1 = 240;
	return;
}
void timer1_CTC_outA_speaker_init(void){
	DDRB |= 1 << PORTB1;
	TCCR1A |= 1 << COM1A0;
	TCCR1B |= 1 << WGM12| 1 << CS11;
	OCR1A = 0;
	return;
}
void timer2_hcsr04_init(void){
	TCCR2A |= 1 << WGM21;				//CTC mode
	TCCR2B |= 1 << CS20 | 1 << CS21 | 1 << CS22;	//1024분주
	OCR2A = 255;
	return;
}

