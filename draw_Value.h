/*
 * draw_Value.h
 *
 *  Created on: Jan 29, 2018
 *      Author: imashio
 */

#include "u8g2.h"		// graphic display library

void draw_MeasLabelUnit(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char *name, const char *unit);

void draw_MeasLabel(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char *name, const char *unit);

void draw_MeasUnit(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char *unit);

void draw_Value(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t value, uint8_t digit, uint8_t frac, uint8_t sign, const char *unit);
void draw_Value_s(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t value, uint8_t digit, uint8_t frac, uint8_t sign, const char *unit);
