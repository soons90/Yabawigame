#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <stdio.h>
#include "I2C_LCD.h"

void I2C_LCD_main(void){
	
	char key_value;
	char long_key_flag = 0;
	I2C_LCD_init();
	lcd_send_string("insert coin");
	move_cursor(1,0);
	while(1){
	}
	return;
}
void lcd_send_command(char command){
	char high_nibble, low_nibble;
	uint8_t data_t[4];
	
	high_nibble = command & 0xF0;
	low_nibble = (command & 0x0F)<<4;
	data_t[0] = high_nibble | 0x0C;		//bl=1, en=1, r/w=0, rs=0 1100
	data_t[1] = high_nibble | 0x08;		//bl=1, en=0, r/w=0, rs=0 1000
	data_t[2] = low_nibble | 0x0C;		//bl=1, en=1, r/w=0, rs=0 1100
	data_t[3] = low_nibble | 0x08;		//bl=1, en=0, r/w=0, rs=0 1000  
	for(char i=0;i<4;i++){
		I2C_sendbyte(I2C_LCD_SLA_W, data_t[i]);
	}
	return;
}
void lcd_send_data(char data){
	char high_nibble, low_nibble;
	uint8_t data_t[4];
	
	high_nibble = data & 0xF0;
	low_nibble = (data & 0x0F)<<4;
	data_t[0] = high_nibble | 0x0D;		//bl=1, en=1, r/w=0, rs=1 1101
	data_t[1] = high_nibble | 0x09;		//bl=1, en=0, r/w=0, rs=1 1001
	data_t[2] = low_nibble | 0x0D;		//bl=1, en=1, r/w=0, rs=1 1101
	data_t[3] = low_nibble | 0x09;		//bl=1, en=0, r/w=0, rs=1 1001
	for(char i=0;i<4;i++){
		I2C_sendbyte(I2C_LCD_SLA_W, data_t[i]);
	}
	return;
}
void lcd_send_string(char *string){
	while(*string != '\0'){
		lcd_send_data(*string);
		string++;
	}
	return;
}
void I2C_LCD_init(void){
	I2C_init();
	lcd_send_command(0x33);
	lcd_send_command(0x32);
	lcd_send_command(0x28);
	lcd_send_command(0x0C);
	lcd_send_command(0x06);
	lcd_send_command(0x01);
	_delay_ms(200);
	return;
}
void move_cursor(char row, char column){
	lcd_send_command(0b10000000 | row << 6 | column);
	return;
}
