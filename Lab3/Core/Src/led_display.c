/*
 * led_display.c
 *
 *  Created on: Oct 29, 2022
 *      Author: DELL
 */

#include "main.h"
#include "led_display.h"

#define NUMBER_OF_7_SEG_LED 4

static uint8_t LED7Conversion[10]={
		0x3f,  // 0
		0x06,  // 1
		0x5b,  // 2
		0x4f,  // 3
		0x66,  // 4
		0x6d,  // 5
		0x7d,  // 6
		0x07,  // 7
		0x7f,  // 8
		0x67   // 9
};

static uint8_t numBuffer[NUMBER_OF_7_SEG_LED];
static uint8_t buffer[NUMBER_OF_7_SEG_LED];

void setLED(void){
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN3_Pin, SET);
}

void update_clock_buffer(uint8_t time1,uint8_t time2){
	numBuffer[0] = time1/10;
	numBuffer[1] = time1%10;
	numBuffer[2] = time2/10;
	numBuffer[3] = time2%10;
}

void update_clock_buffer1(uint8_t time1) {
	numBuffer[0] = time1/10;
	numBuffer[1] = time1%10;
}

void update_clock_buffer2(uint8_t time2) {
	numBuffer[2] = time2/10;
	numBuffer[3] = time2%10;
}

void update_seven_segment_driver(uint8_t index){
	switch (index){
	case 0:
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,1);
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,0);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,0);
		buffer[0]=LED7Conversion[numBuffer[0]];
		buffer[2]=LED7Conversion[numBuffer[2]];
		seven_segment_driver_1(0);
		seven_segment_driver_2(2);
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin,1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin,1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin,0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin,0);
		buffer[1]=LED7Conversion[numBuffer[1]];
		buffer[3]=LED7Conversion[numBuffer[3]];
		seven_segment_driver_1(1);
		seven_segment_driver_2(3);
		break;
	}
}

void seven_segment_driver_1(uint8_t index){
	HAL_GPIO_WritePin(SEG_A1_GPIO_Port, SEG_A1_Pin, !((buffer[index]>>0)&0x01));
	HAL_GPIO_WritePin(SEG_B1_GPIO_Port, SEG_B1_Pin, !((buffer[index]>>1)&0x01));
	HAL_GPIO_WritePin(SEG_C1_GPIO_Port, SEG_C1_Pin, !((buffer[index]>>2)&0x01));
	HAL_GPIO_WritePin(SEG_D1_GPIO_Port, SEG_D1_Pin, !((buffer[index]>>3)&0x01));
	HAL_GPIO_WritePin(SEG_E1_GPIO_Port, SEG_E1_Pin, !((buffer[index]>>4)&0x01));
	HAL_GPIO_WritePin(SEG_F1_GPIO_Port, SEG_F1_Pin, !((buffer[index]>>5)&0x01));
	HAL_GPIO_WritePin(SEG_G1_GPIO_Port, SEG_G1_Pin, !((buffer[index]>>6)&0x01));
}

void seven_segment_driver_2(uint8_t index){
	HAL_GPIO_WritePin(SEG_A2_GPIO_Port, SEG_A2_Pin, !((buffer[index]>>0)&0x01));
	HAL_GPIO_WritePin(SEG_B2_GPIO_Port, SEG_B2_Pin, !((buffer[index]>>1)&0x01));
	HAL_GPIO_WritePin(SEG_C2_GPIO_Port, SEG_C2_Pin, !((buffer[index]>>2)&0x01));
	HAL_GPIO_WritePin(SEG_D2_GPIO_Port, SEG_D2_Pin, !((buffer[index]>>3)&0x01));
	HAL_GPIO_WritePin(SEG_E2_GPIO_Port, SEG_E2_Pin, !((buffer[index]>>4)&0x01));
	HAL_GPIO_WritePin(SEG_F2_GPIO_Port, SEG_F2_Pin, !((buffer[index]>>5)&0x01));
	HAL_GPIO_WritePin(SEG_G2_GPIO_Port, SEG_G2_Pin, !((buffer[index]>>6)&0x01));
}
