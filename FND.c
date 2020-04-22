/*
 * FND.c
 *
 * Created: 2020-03-30 오후 8:50:50
 *  Author: 안순남
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "FND.h"

unsigned char FND_font[10] = {
	1 << FND_a | 1 << FND_b | 1 << FND_c | 1 << FND_d | 1 << FND_e | 1 << FND_f,	//0
	1 << FND_b | 1 << FND_c,														//1
	1 << FND_a | 1 << FND_b | 1 << FND_d | 1 << FND_e | 1 << FND_g,					//2
	1 << FND_a | 1 << FND_b | 1 << FND_c | 1 << FND_d | 1 << FND_g,					//3
	1 << FND_f | 1 << FND_g | 1 << FND_b | 1 << FND_c,								//4
	1 << FND_a | 1 << FND_f | 1 << FND_g | 1 << FND_c | 1 << FND_d,					//5
	1 << FND_a | 1 << FND_c | 1 << FND_d | 1 << FND_e | 1 << FND_f | 1 << FND_g,					//6
	1 << FND_a | 1 << FND_b | 1 << FND_c,											//7
	1 << FND_a | 1 << FND_b | 1 << FND_c | 1 << FND_d | 1 << FND_e | 1 << FND_f | 1 << FND_g,//8
	1 << FND_a | 1 << FND_b | 1 << FND_c | 1 << FND_d | 1 << FND_g | 1 << FND_f		//9
};
int FND_main(void)
{
	
	/* Replace with your application code */
	while (1)
	{
		FND_sight(4);
		}

}

void FND_init(void){ // PORTD 입출력 설정
	DDRD |= 1<< PORTD0 | 1<< PORTD1 | 1<< PORTD3 | 1<< PORTD4 | 1<< PORTD5 | 1<< PORTD6 | 1<< PORTD7;
	PORTD |= 0b00000000;
	return;
}

void FND_sight(char num){
		PORTD = FND_font[num];
	
}