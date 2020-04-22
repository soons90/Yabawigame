/*
 * timer.h
 *
 * Created: 2019-09-20 오후 12:58:23
 *  Author: 정경윤
 */ 


#ifndef TIMER_H_
#define TIMER_H_

void timer0_compA_msec_int_init(void);
void timer1_fast_PWM_init(void);
void timer2_fast_PWM_init(void);
void timer1_fast_PWM_survo_motor_init(void);
void timer1_CTC_outA_speaker_init(void);
void timer2_hcsr04_init(void);

volatile unsigned int msec;
volatile char sec, min;
volatile char time_print_flag, sw_start_flag;
volatile unsigned int sw_msec;
volatile char sw_sec, sw_min;

#endif /* TIMER_H_ */