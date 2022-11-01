/*
 * software_timer.c
 *
 *  Created on: Oct 29, 2022
 *      Author: DELL
 */

#include "main.h"
#include "input_reading.h"
#include "software_timer.h"

int timer0_counter;
int timer0_flag = 0;
int led_7_flag = 0;
int blink_flag = 0;

void setTimer(int duration){
	timer0_counter = duration/TIMER_CYCLE;
	timer0_flag = 0;
}

void timer_run(){
	if (timer0_counter > 0){
		timer0_counter--;
		if (timer0_counter > 50) led_7_flag = 1;
		else  led_7_flag = 0;
		if(timer0_counter % 25 == 0) blink_flag = 1;
		else blink_flag = 0;
		if (timer0_counter == 0) timer0_flag = 1;
	}
}
