/*
 * jjanggaembbo.c
 *
 * Created: 2020-04-06 오전 12:08:47
 * Author : 안순남
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "I2C_LCD.h"
#include "switch.h"
#include "FND.h"
#include "timer.h"
#include "Speaker.h"
#define GAME_READY 0
#define GAME_START 1
#define GAME_END 2
#define COIN 4
extern void music_player(int *tune, int*beat);

void game_ready(char key_value);
void game_start(char key_value);
void game_end(void);
char keyscan(void);
char game_state = GAME_READY;

int main(void)
{
	char key_value; // 입력 받는 키 저장하는 변수
	char long_key_flag = 0; // 채터링 플래그
	I2C_LCD_init();
	FND_init();
	timer1_CTC_outA_speaker_init();
	switch_init();	//레지스터셋팅
	lcd_send_string("  Insert Coin");
    while (1) 
    {
		if(long_key_flag){ // 채터링 방지 디바운스
			if(keyscan() != 0){ 
				_delay_us(10); 
				key_value = keyscan(); // 입력 받은 키 값을 저장
				if(key_value != 0){ // 키가 입력 되면
					long_key_flag = 0; // 다시 받을 준비
					if(game_state == GAME_READY)game_ready(key_value); // 상태에 따른 함수 호출
					else if(game_state == GAME_START)game_start(key_value);
					
				}
			}
		}
		else { // 키 입력이 없을때 계속 키 입력 받을 준비
			if(keyscan() == 0){
				_delay_us(100);
				if(keyscan() == 0){
					long_key_flag = 1;
				}
			}
		}
		delay_ms(1);	
    }
	return;
}

void game_ready(char key_value){ // 게임 준비 상태
	FND_sight(0);
	move_cursor(0,0); // lcd창 처음으로
	lcd_send_string("  Insert Coin");
	if(key_value == COIN){ // 코인버튼이 눌리면 게임이 시작됨
		move_cursor(0,0);
		lcd_send_string("   Game Start ");
		key_sound();
		game_state = GAME_START;
		delay_ms(500);
		move_cursor(0,0);
		lcd_send_string("       3      ");
		delay_ms(500);
		move_cursor(0,0);
		lcd_send_string("       2      ");
		delay_ms(500);
		move_cursor(0,0);
		lcd_send_string("       1      ");
		delay_ms(500);
		move_cursor(0,0);
		lcd_send_string(" Choice Button  ");
	}
	return;
}

void game_start(char key_value){ // 게임 시작 상태
	
	char correct;
	correct = random()%3+1;
	
	if(correct == key_value){ // 정답을 찾으면
		
		move_cursor(0,0);
		lcd_send_string("    WIN!!!    "); // 이겼다
		win_sound();
		delay_ms(2000);
		game_end(); // 게임 마무리 함수 호출
		
	}
	else if(key_value == COIN){}
	else{ // 답이 틀리면
		move_cursor(0,0);
		lcd_send_string("    LOSE...   "); // 졌다
		lose_sound();
		game_state = GAME_READY; // 다시 준비
		delay_ms(2000);
		game_ready(0);
		
	}
	return;
}

void game_end(void){ //게임 마무리
	char result = 0;
	result = random()%9+1; // 9이하의 자연수
	move_cursor(0,0);
	lcd_send_string("    GET MEDAL    ");
	game_state = GAME_READY; // 다시 준비
	FND_sight(result);
	endbeat();
	delay_ms(3000);
	game_ready(0);
	return;
}

char keyscan(void){ //키 값 변환 함수
	switch(PINC & 0b00000111){
		case 0b00000001 : return 1; break; //button 1
		case 0b00000010 : return 2; break; //button 2
		case 0b00000100 : return 3; break; //button 3
		default: break;
	}
	if(PINB & 0b00000001){ //button 4 (coin button)
		return 4;
	}
	return 0; // 아무키도 입력받지 않았을 때 0 반환
}