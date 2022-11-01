/*
 * button_processing.c
 *
 *  Created on: Oct 29, 2022
 *      Author: DELL
 */

#include "output_processing.h"

#define RED 0
#define AMBER 1
#define GREEN 2

enum MODE { MODE_1 , MODE_2 , MODE_3 , MODE_4 } ;

enum MODE Mode = MODE_1;

static uint8_t counter_mode2, counter_mode3, counter_mode4;
static uint8_t executive0, executive1, executive2;
int init = 0;

void fsm_for_output_processing (void){
	switch (Mode){
	case MODE_1:
		update_seven_segment_driver(led_7_flag);
		if (is_button_pressed(0) == 1){
			if(executive0 == 0) {
				Mode = MODE_2;
				counter_mode2 = 0;
				LED_TRAFFIC_INIT();
				setTimer(1000);
				executive0 = 1;
			}
		} else {
			executive0 = 0;
		}
		if (timer0_flag == 1){
			if(init == 0) {
				LED_TRAFFIC_INIT();
				init = 1;
			}
			LED_TRAFFIC_RUN();
			setTimer(1000);
		}
		break;
	case MODE_2:
//		HAL_GPIO_TogglePin(LED_TOGGLE_GPIO_Port, LED_TOGGLE_Pin);
		update_clock_buffer(counter_mode2, 2);
		update_seven_segment_driver(led_7_flag);
		if (blink_flag){
			HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
			HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin);
		}
		if (is_button_pressed(0)){
			if(executive0 == 0) {
				executive0 = 1;
				Mode = MODE_3;
				counter_mode3 = 0;
				LED_TRAFFIC_INIT();
				setTimer(1000);
			}
		} else {
			executive0 = 0;
		}
		if (is_button_pressed(1)){
			if(executive1 == 0) {
				executive1 = 1;
				counter_mode2 = (counter_mode2 + 1) % 99;
			}
		} else executive1 = 0;
		if (is_button_pressed(2)){
			if(executive2 == 0) {
				executive2 = 1;
				LED_TRAFFIC_STORE_BUFFER(counter_mode2, RED);
			}
		} else {
			executive2 = 0;
		}
		if (timer0_flag == 1){
			setTimer(1000);
		}
		break;
	case MODE_3:
		update_clock_buffer(counter_mode3, 3);
		update_seven_segment_driver(led_7_flag);
		if (blink_flag){
			HAL_GPIO_TogglePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin);
			HAL_GPIO_TogglePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin);
		}
		if (is_button_pressed(0)){
			if(executive0 == 0) {
				executive0 = 1;
				Mode = MODE_4;
				counter_mode4 = 0;
				LED_TRAFFIC_INIT();
				setTimer(1000);
			}
		} else {
			executive0 = 0;
		}
		if (is_button_pressed(1)){
			if(executive1 == 0) {
				executive1 = 1;
				counter_mode3 = (counter_mode3 + 1) % 99;
			}
		} else {
			executive1 = 0;
		}
		if (is_button_pressed(2)){
			if(executive2 == 0) {
				executive2 = 1;
				LED_TRAFFIC_STORE_BUFFER(counter_mode3, AMBER);
			}
		} else {
			executive2 = 0;
		}
		if (timer0_flag == 1){
			setTimer(1000);
		}
		break;
	case MODE_4:
		update_clock_buffer(counter_mode4, 4);
		update_seven_segment_driver(led_7_flag);
		if (blink_flag){
			HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
			HAL_GPIO_TogglePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin);
		}
		if (is_button_pressed(0)){
			if(executive0 == 0) {
				executive0 = 1;
				Mode = MODE_1;
				LED_TRAFFIC_LOAD_BUFFER();
				LED_TRAFFIC_INIT();
				setTimer(1000);
			}
		} else {
			executive0 = 0;
		}
		if (is_button_pressed(1)){
			if(executive1 == 0) {
				executive1 = 1;
				counter_mode4 = (counter_mode4 + 1) % 99;
			}
		} else {
			executive1 = 0;
		}
		if (is_button_pressed(2)){
			if(executive2 == 0) {
				executive2 = 1;
				LED_TRAFFIC_STORE_BUFFER(counter_mode4, GREEN);
			}
		} else {
			executive2 = 0;
		}
		if (timer0_flag == 1){
			setTimer(1000);
		}
		break;
	default:
		Mode = MODE_1;
	}
}
