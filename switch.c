#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <stdio.h>
#include "switch.h"


int switch_main(void){
	
}

void switch_init(void){
	DDRC |= 0x00;
	DDRB |= 0x00;
}
