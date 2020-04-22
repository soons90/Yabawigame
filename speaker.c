/*
 * speaker.c
 *
 * Created: 2019-09-20 오후 12:52:31
 *  Author: 정경윤
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "timer.h"
#include "Speaker.h"

int He_Pirate[] =
{
	RE_05, RE_05, RE_05, RE_05,
	RE_05, RE_05, RE_05, LA_04, DO_05,
	RE_05, RE_05, RE_05, MI_05,
	FA_05, FA_05, FA_05, SO_05,
	MI_05, MI_05, RE_05, DO_05,
	DO_05, RE_05, SIRENCE, LA_04, DO_05,
	RE_05, RE_05, RE_05, MI_05,
	FA_05, FA_05, FA_05, SO_05,
	MI_05, MI_05, RE_05, DO_05,
	RE_05, SIRENCE, SIRENCE, LA_04, DO_05,
	RE_05, RE_05, RE_05, FA_05,
	SO_05, SO_05, SO_05, LA_05,
	LA_05s, LA_05s, LA_05, SO_05,
	
	LA_05, RE_05, SIRENCE, RE_05, MI_05,
	FA_05, FA_05, SO_05,
	LA_05, RE_05, SIRENCE, RE_05, FA_05,
	MI_05, MI_05, FA_05, RE_05,
	MI_05, SIRENCE, SIRENCE, LA_05, DO_07,
	RE_07, RE_07, RE_07, MI_07,
	FA_07, FA_07, FA_07, SO_07,
	MI_07, MI_07, RE_07, DO_07,
	DO_07, RE_07, SIRENCE, LA_05, DO_07,
	RE_07, RE_07, RE_07, MI_07,
	FA_07, FA_07, FA_07, SO_07,
	MI_07, MI_07, RE_07, DO_07,
	RE_07, SIRENCE, SIRENCE, LA_05, DO_07,
	RE_07, RE_07, RE_07, FA_07,
	SO_07, SO_07, SO_07, LA_07,
	LA_07s, LA_07s, LA_07, SO_07,
	LA_07, RE_07, SIRENCE, RE_07, MI_07,
	FA_07, FA_07, SO_07,
	LA_07, RE_07, SIRENCE, RE_07, FA_07,
	MI_07, MI_07, RE_07, DO_07,
	RE_07, RE_07, MI_07,
	
	FA_07, FA_07, FA_07, SO_07,
	LA_07, FA_07, SIRENCE, SIRENCE, FA_07, RE_07,
	LA_05, SIRENCE, SIRENCE, SIRENCE,
	LA_05s, SIRENCE, SIRENCE, SO_07, RE_07,
	LA_05s, SIRENCE, SIRENCE, SIRENCE,
	MI_07, MI_07, RE_07,
	FA_05, SIRENCE, FA_05, SO_05,
	LA_05, LA_05, LA_05,
	LA_05s, LA_05,SIRENCE , SIRENCE,
	SO_05, SO_05, SO_05,
	SO_05, LA_05, SIRENCE, SIRENCE,
	LA_05, LA_05, LA_05,
	LA_05s, LA_05, SIRENCE, SIRENCE,
	SO_05, FA_05, MI_05,
	RE_05, SIRENCE, SIRENCE, RE_05, MI_05,
	FA_05, SO_05, LA_05,
	SO_05, FA_05, MI_05,
	FA_05, SO_05, LA_05,
	SO_05, SIRENCE, SIRENCE, FA_05, SO_05,
	LA_05, SIRENCE, SIRENCE, SO_05, FA_05,
	MI_05, FA_05, MI_05,
	RE_05, SIRENCE, SIRENCE, MI_05, DO_05,
	RE_05, SIRENCE, SIRENCE, RE_07, MI_07,
	
	FA_07, SIRENCE, SIRENCE, MI_07, FA_07,
	SO_07, FA_07, SO_07,
	LA_07, SO_07, FA_07,
	RE_07, SIRENCE, SIRENCE, RE_07, MI_07,
	FA_07, SO_07, LA_07,
	LA_07s, RE_07, SO_07,
	FA_07, SIRENCE, SIRENCE, SO_07, MI_07,
	RE_07, SIRENCE, SIRENCE, MI_07, DO_07s,
	LA_07, SIRENCE, SIRENCE, LA_07s, SIRENCE, SIRENCE,
	LA_07, LA_07, LA_07,
	LA_07, SO_07, SIRENCE, SIRENCE,
	SO_07, SIRENCE, SIRENCE,
	FA_07, SIRENCE, SIRENCE,
	FA_07, SO_07, MI_07,
	RE_07, RE_07, MI_07, FA_07,
	LA_07, RE_07, MI_07, FA_07,
	LA_07s, RE_07, MI_07, FA_07,
	LA_07, LA_07, DO_06,
	LA_07, SO_07, SIRENCE, SIRENCE,
	SO_07, SIRENCE, SIRENCE,
	FA_07, SIRENCE, SIRENCE,
	FA_07, SO_07, MI_07,
	RE_07, SIRENCE, SIRENCE,
	RE_05, '/0'
};
int He_Pirate_Beat[] =
{
	BEAT_1_4, BEAT_1_8, BEAT_1_4, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_16, BEAT_1_16, BEAT_1_16,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_4, BEAT_1_2,
	BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_8, BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_8, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_2, BEAT_1_8, BEAT_1_8, BEAT_1_8,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_8, BEAT_1_8, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_4, BEAT_1_4, BEAT_1_4,
	BEAT_1_2, BEAT_1_8, BEAT_1_4,
	BEAT_1
};
int school_bell_tune[] =				//학교종
{
	SO_07, SO_07, LA_07, LA_07, SO_07, SO_07, MI_07,
	SO_07, SO_07, MI_07, MI_07, RE_07,
	SO_07, SO_07, LA_07, LA_07, SO_07, SO_07, MI_07,
	SO_07, MI_07, RE_07, MI_07, DO_07, '\0'
};
int school_bell_beat[] = {
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_2,
	BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1_4, BEAT_1
};



void speaker_main(void){
	
	int Hz = 1000UL;
	timer1_CTC_outA_speaker_init();
	//OCR1AL = 1000 & 0xff;
	//OCR1AH = (1000 >> 8) & 0xff;
	while(1){
		music_player(school_bell_tune, school_bell_beat);
		_delay_ms(3000);
		/*for(int i=1;i<10;i++){
			beep(i);
			_delay_ms(1000);
		}*/
		//music_player(He_Pirate, He_Pirate_Beat);
		//_delay_ms(2000);
		/*Hz += 1000UL;
		OCR1A = F_CPU / 8 / 2 / Hz - 1;
		if(Hz >= 15000UL)Hz = 1000;
		_delay_ms(1000);*/
	}
	return;
}
void music_player(int *tune, int *beat){
	while(*tune != '\0'){
		OCR1A = F_CPU / 8 / 2 / *tune - 1;
		delay_ms(*beat);
		tune++;
		beat++;
		OCR1A = 0;
		_delay_ms(10);
	}
	return;
}
void delay_ms(int ms){
	while(ms--)_delay_ms(1);
	return;
}
void beep(char repeat){
	for(int i=0;i<repeat;i++){
		OCR1A = 500;
		_delay_ms(200);
		OCR1A = 0;
		_delay_ms(200);
	}
	return;
}
void siren(char repeat){
	OCR1A = 900;
	for(int i=0;i<repeat;i++){
		for(int i=0;i<1000;i++){
			OCR1A++;
			_delay_ms(2);
		}
		for(int i=0;i<1000;i++){
			OCR1A--;
			_delay_ms(2);
		}
	}
	OCR1A = 0;
	return;
}

void key_sound(void){
	OCR1A = 500;
	_delay_ms(100);
	OCR1A = 600;
	_delay_ms(100);
	OCR1A = 700;
	_delay_ms(100);
	OCR1A = 0;
	return;
}

void lose_sound(void){
	OCR1A = 500;
	_delay_ms(100);
	OCR1A = 0;
	OCR1A = 500;
	_delay_ms(100);
	OCR1A = 0;
}

void win_sound(void){ //국뽕비트
	OCR1A = 1000;
	_delay_ms(200);
	OCR1A = 0;
	_delay_ms(200);
	OCR1A = 1000;
	_delay_ms(200);
	OCR1A = 0;
	_delay_ms(200);
	OCR1A = 1000;
	_delay_ms(100);
	OCR1A = 0;
	_delay_ms(100);
	OCR1A = 1000;
	_delay_ms(100);
	OCR1A = 0;
	_delay_ms(100);
	OCR1A = 1000;
	_delay_ms(100);
	OCR1A = 0;
	_delay_ms(300);	
	
	OCR1A = 1000;
	_delay_ms(100);
	OCR1A = 0;
	_delay_ms(100);
	OCR1A = 1000;
	_delay_ms(100);
	OCR1A = 0;
	_delay_ms(100);
	OCR1A = 1000;
	_delay_ms(100);
	OCR1A = 0;
	_delay_ms(100);
	OCR1A = 1000;
	_delay_ms(300);
	OCR1A = 0;
	_delay_ms(100);
	OCR1A = 1000;
	_delay_ms(100);
	OCR1A = 0;
	_delay_ms(100);
	OCR1A = 1000;
	_delay_ms(100);
	OCR1A = 0;
	
	
	return;
}

void endbeat(void){
	for(int i = 0; i<1100; i+=100){
		OCR1A = i;
		_delay_ms(100);
	}
	for(int j = 1000; j>=0; j-=100){
		OCR1A = j;
		_delay_ms(100);
	}
}