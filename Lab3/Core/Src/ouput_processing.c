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

// counter_mode2, counter_mode3, counter_mode4 to save time of led_traffic
static uint8_t counter_mode2, counter_mode3, counter_mode4;

// executive0, executive1, executive2 to avoid wrong mode when simulation by press button.
// Ex: If I press button_0 to change mode 1 to mode 2 and then in mode 2 button_0 is also press
// so it change to mode 3.
static uint8_t executive0, executive1, executive2;

// variable init to check INIT_TRAFFIC_LED when we start simulation
int init = 0, index_led7 = 0;

// FSM_MODEL is call in main (while)
void fsm_for_output_processing (void){
	switch (Mode){
	case MODE_1:
		// UPADTE AND DISPLAY LED7
		if(led_7_flag) {
			update_LED7_driver(index_led7);
			index_led7++;
			if(index_led7 == 4) index_led7 = 0;
			setLED7Timer(250);
		}
		// BUTTON_0 PRESS
		if (is_button_pressed(0) == 1){
			if(executive0 == 0) {
				executive0 = 1;
				Mode = MODE_2;
				counter_mode2 = 0;
				LED_TRAFFIC_INIT();
				setTimer(1000);
			}
		} else {
			executive0 = 0;
		}
		// SET_TIMER 1S IF DONT PRESS AND INIT LED_TRAFFIC
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
		// UPDATE AND DISPLAY LED7
		update_all_clock_buffer(counter_mode2, 2);
		if(led_7_flag) {
			update_LED7_driver(index_led7);
			index_led7++;
			if(index_led7 == 4) index_led7 = 0;
			setLED7Timer(250);
		}
		// BLINK ALL LED RED 2HZ
		if (blink_flag){
			HAL_GPIO_TogglePin(LED_RED1_GPIO_Port, LED_RED1_Pin);
			HAL_GPIO_TogglePin(LED_RED2_GPIO_Port, LED_RED2_Pin);
			setBlinkLedTimer(250);
		}
		// BUTTON_0 PRESS
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
		// BUTTON_1 PRESS
		if (is_button_pressed(1)){
			if(executive1 == 0) {
				executive1 = 1;
				counter_mode2 = (counter_mode2 + 1) % 99;
			}
		} else executive1 = 0;
		// BUTTON_2 PRESS
		if (is_button_pressed(2)){
			if(executive2 == 0) {
				executive2 = 1;
				LED_TRAFFIC_STORE_BUFFER(counter_mode2, RED);
			}
		} else {
			executive2 = 0;
		}
		// SET_TIMER 1S IF DONT PRESS
		if (timer0_flag == 1){
			setTimer(1000);
		}
		break;
	case MODE_3:
		// UPDATE AND DISPLAY LED7
		update_all_clock_buffer(counter_mode3, 3);
		if(led_7_flag) {
			update_LED7_driver(index_led7);
			index_led7++;
			if(index_led7 == 4) index_led7 = 0;
			setLED7Timer(250);
		}
		// BLINK ALL LED AMBER 2HZ
		if (blink_flag){
			HAL_GPIO_TogglePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin);
			HAL_GPIO_TogglePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin);
			setBlinkLedTimer(250);
		}
		// BUTTON_0 PRESS
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
		// BUTTON_1 PRESS
		if (is_button_pressed(1)){
			if(executive1 == 0) {
				executive1 = 1;
				counter_mode3 = (counter_mode3 + 1) % 99;
			}
		} else {
			executive1 = 0;
		}
		// BUTTON_2 PRESS
		if (is_button_pressed(2)){
			if(executive2 == 0) {
				executive2 = 1;
				LED_TRAFFIC_STORE_BUFFER(counter_mode3, AMBER);
			}
		} else {
			executive2 = 0;
		}
		// SET_TIMER 1S IF DONT PRESS
		if (timer0_flag == 1){
			setTimer(1000);
		}
		break;
	case MODE_4:
		// UPDATE AND DISPLAY LED7
		update_all_clock_buffer(counter_mode4, 4);
		if(led_7_flag) {
			update_LED7_driver(index_led7);
			index_led7++;
			if(index_led7 == 4) index_led7 = 0;
			setLED7Timer(250);
		}
		// BLINK ALL LED GREEN 2HZ
		if (blink_flag){
			HAL_GPIO_TogglePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin);
			HAL_GPIO_TogglePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin);
			setBlinkLedTimer(250);
		}
		// BUTTON_0 PRESS
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
		// BUTTON_1 PRESS
		if (is_button_pressed(1)){
			if(executive1 == 0) {
				executive1 = 1;
				counter_mode4 = (counter_mode4 + 1) % 99;
			}
		} else {
			executive1 = 0;
		}
		// BUTTON_2 PRESS
		if (is_button_pressed(2)){
			if(executive2 == 0) {
				executive2 = 1;
				LED_TRAFFIC_STORE_BUFFER(counter_mode4, GREEN);
			}
		} else {
			executive2 = 0;
		}
		// SET_TIMER 1S IF DONT PRESS
		if (timer0_flag == 1){
			setTimer(1000);
		}
		break;
	default:
		Mode = MODE_1;
	}
}
