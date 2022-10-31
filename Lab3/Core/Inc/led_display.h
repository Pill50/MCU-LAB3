/*
 * led_display.h
 *
 *  Created on: Oct 29, 2022
 *      Author: DELL
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

void update_seven_segment_driver(uint8_t index);
void seven_segment_driver_1(uint8_t index);
void seven_segment_driver_2(uint8_t index);
void update_clock_buffer(uint8_t time1, uint8_t time2);
void update_clock_buffer1(uint8_t time1);
void update_clock_buffer2(uint8_t time2);
void setLED(void);

#endif /* INC_LED_DISPLAY_H_ */
