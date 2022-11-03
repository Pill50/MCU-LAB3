/*
 * software_timer.c
 *
 *  Created on: Oct 29, 2022
 *      Author: DELL
 */

#include "main.h"
#include "input_reading.h"
#include "software_timer.h"

// define counter
int timer0_counter;
int led7_counter;
int blink_counter;

//define flag
int timer0_flag = 0;	//time_flag
int led_7_flag = 0;		//led7_flag
int blink_flag = 0;		//led_traffic_blink_flag

void setTimer(int duration){
	timer0_counter = duration/TIMER_CYCLE;
	timer0_flag = 0;
}

void setLED7Timer(int duration){
	led7_counter = duration/TIMER_CYCLE;
	led_7_flag = 0;
}

void setBlinkLedTimer(int duration){
	blink_counter = duration/TIMER_CYCLE;
	blink_flag = 0;
}

void timer_run(){
	if (timer0_counter > 0){
		timer0_counter--;
		if (timer0_counter == 0) timer0_flag = 1;
	}
	if (led7_counter > 0){
		led7_counter--;
		if (led7_counter == 0) led_7_flag = 1;
	}
	if (blink_counter > 0){
		blink_counter--;
		if (blink_counter == 0) blink_flag = 1;
	}
}
