/*
 * CircularMeter.h
 *
 *  Created on: Jan 28, 2018
 *      Author: imashio
 */

draw_CircularMeter_Init(uint8_t x, uint8_t  y, uint8_t  r, uint8_t tick_length, int16_t rad_offset, int16_t rad_max, uint8_t tick_num, uint8_t dot_num, int8_t dir, int16_t value_min, int16_t value_max);

draw_CircularMeter(u8g2_t *u8g2, int16_t value);
