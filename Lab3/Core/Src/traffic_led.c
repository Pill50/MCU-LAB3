/*
 * traffic_led.c
 *
 *  Created on: Oct 29, 2022
 *      Author: DELL
 */


#include "main.h"
#include "traffic_led.h"
#include "led_display.h"

#define N0_OF_LED 3

#define RED 0
#define AMBER 1
#define GREEN 2

static uint8_t bufferTimerForLED[N0_OF_LED];
static uint8_t counterRED1, counterAMBER1, counterGREEN1,  counterRED2, counterAMBER2, counterGREEN2;
static uint8_t timeRED, timeAMBER, timeGREEN;

void LED_TRAFFIC_INIT(void){
	HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
	HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
	HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, SET);
	HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, SET);
	HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
	HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
}

void LED_TRAFFIC_LOAD_BUFFER(void){
	counterRED1 = bufferTimerForLED[RED];
	counterAMBER1 = bufferTimerForLED[AMBER];
	counterGREEN1 = bufferTimerForLED[GREEN];
	counterRED2 = bufferTimerForLED[RED];
	counterAMBER2 = bufferTimerForLED[AMBER];
	counterGREEN2 = bufferTimerForLED[GREEN];
	timeRED = bufferTimerForLED[RED];
	timeAMBER = bufferTimerForLED[AMBER];
	timeGREEN = bufferTimerForLED[GREEN];
}

void LED_TRAFFIC_STORE_BUFFER(uint8_t time, uint8_t index){
	bufferTimerForLED[index] = time;
}

void LED_VERTICAL_RUN(void) {
	//GREEN1 - ON
	if (counterGREEN2 > 0){
		update_clock_vertical(counterGREEN2);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, RESET);
		counterGREEN2--;

	}
	//AMBER1 - ON
	else if (counterAMBER2 > 0){
		update_clock_vertical(counterAMBER2);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, SET);
		HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		counterAMBER2--;
	}
	//RED1 - ON
	else if (counterRED2 > 0){
		update_clock_vertical(counterRED2);
		HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, RESET);
		HAL_GPIO_WritePin(LED_AMBER1_GPIO_Port, LED_AMBER1_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, SET);
		counterRED2--;
	}
	if(counterRED2 == 0) {
		counterRED2 = timeRED;
		counterAMBER2 = timeAMBER;
		counterGREEN2 = timeGREEN;
	}
}

void LED_HORIZONTAL_RUN(void) {
	//RED2 - ON
	if (counterRED1 > 0){
		update_clock_horizontal(counterRED1);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, RESET);
		HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		counterRED1--;
	}
	//AMBER2 - ON
	else if (counterAMBER1 > 0){
		update_clock_horizontal(counterAMBER1);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, RESET);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, SET);
		counterAMBER1--;
	}
	//GREEN2 - ON
	else if (counterGREEN1 > 0){
		update_clock_horizontal(counterGREEN1);
		HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, SET);
		HAL_GPIO_WritePin(LED_AMBER2_GPIO_Port, LED_AMBER2_Pin, SET);
		HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, RESET);
		counterGREEN1--;
	}
	if(counterGREEN1 == 0) {
		counterRED1 = timeRED;
		counterAMBER1 = timeAMBER;
		counterGREEN1 = timeGREEN;
	}
}

void LED_TRAFFIC_RUN(void) {
	LED_HORIZONTAL_RUN();
	LED_VERTICAL_RUN();
}
