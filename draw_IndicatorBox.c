/*
 * drawIndicatorBox.c
 *
 *  Created on: Jan 29, 2018
 *      Author: imashio
 */

#include "u8g2.h"		// graphic display library


#define	idct_font		u8g2_font_micro_tr

void draw_IndicatorBox(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color, const char *str){
	uint8_t	str_offset;
	u8g2_SetDrawColor(u8g2, 1); // default color
	u8g2_SetFont(u8g2, idct_font);
	if( color == 1 ){
		u8g2_DrawRBox(u8g2, x, y, width, height, 2);
		u8g2_SetDrawColor(u8g2, 2); // xor color
		u8g2_SetFontMode(u8g2, 1); // set font mode transparent
	}else{
	  u8g2_DrawRFrame(u8g2, x, y, width, height, 2);
	}
	str_offset = ( (width - StrLength(str)*4)>>1 ) + 1;
	u8g2_DrawStr(u8g2, x+str_offset, y+(height-2), str);
	u8g2_SetFontMode(u8g2, 0); // set font mode normal
	u8g2_SetDrawColor(u8g2, 1); // default color
}

