/*
 * software_timer.h
 *
 *  Created on: Oct 29, 2022
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIMER_CYCLE 10;

extern int timer0_flag;
extern int led_7_flag ;
extern int blink_flag;
void setTimer(int duration);
void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */