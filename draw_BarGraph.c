/*
 * BarGraph.c
 *
 *  Created on: Jan 29, 2018
 *      Author: imashio
 */

#include "u8g2.h"		// graphic display library


#define	bar_font		u8g2_font_7x14B_tf


void draw_BarGraph(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t value, uint16_t value_min, uint16_t value_max){
	uint8_t	tick_x;
	u8g2_SetFont(u8g2, bar_font);

	u8g2_SetDrawColor(u8g2, 0); // erase color
	u8g2_DrawBox(u8g2, 0, 0, width, height); // erase bar

	u8g2_SetDrawColor(u8g2, 1); // default color
	u8g2_DrawBox(u8g2, x, y+1, (uint8_t)( value/(double)value_max*width)+1, height-2);

	u8g2_SetDrawColor(u8g2, 2); // xor color
	for(uint8_t n=2;n<=8;n++){
		tick_x = (1000*n)/(double)value_max * width;
		u8g2_DrawLine(u8g2, tick_x+1, 0, tick_x+1, y+height-1);
	}

	u8g2_SetDrawColor(u8g2, 2); // xor color
	u8g2_SetFontMode(u8g2, 1); // set font mode transparent
	u8g2_DrawStr(u8g2, x+1, y+height-2, u8g2_u16toa(value,4) );
	u8g2_SetFontMode(u8g2, 0); // set font mode normal
	u8g2_SetDrawColor(u8g2, 1); // default color
}
