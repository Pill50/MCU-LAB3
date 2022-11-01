/*
 * input_reading.c
 *
 *  Created on: Oct 29, 2022
 *      Author: DELL
 */

#include "main.h"
#include "input_reading.h"

#define N0_OF_BUTTONS 					3
#define BUTTON_IS_PRESSED 				GPIO_PIN_RESET
#define BUTTON_IS_RELEASED 				GPIO_PIN_SET

static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];

static uint16_t buttonPin[N0_OF_BUTTONS] = {BUTTON_0_Pin, BUTTON_1_Pin, BUTTON_2_Pin};

void button_reading_Init(void){
	for (int i = 0; i < N0_OF_BUTTONS; i++){
		debounceButtonBuffer1[i] = BUTTON_IS_RELEASED;
		debounceButtonBuffer2[i] = BUTTON_IS_RELEASED;
		buttonBuffer[i] = BUTTON_IS_RELEASED;
	}
}

void button_reading(void){
	for(int i = 0; i < N0_OF_BUTTONS; i++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOB, buttonPin[i]);
		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
			buttonBuffer[i] = debounceButtonBuffer1[i];
		}
	}
}

unsigned char is_button_pressed(uint8_t index){
	if(index >= N0_OF_BUTTONS) return 0;
	if (buttonBuffer[index] == BUTTON_IS_PRESSED){
		return 1;
	}
	else return 0;
}

