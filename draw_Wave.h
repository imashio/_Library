/*
 * draw_Wave.h
 *
 *  Created on: Nov 11, 2018
 *      Author: imashio
 */

#include "u8g2.h"		// graphic display library

void draw_Wave(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t value_min, int16_t value_max, int16_t *value, uint16_t index);
