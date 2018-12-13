/*
  draw_Wavw.c

   Created on: Nov 11, 2018
       Author: imashio
 */

#include "u8g2.h"		// graphic display library

#define font_width	4
#define font_height	5
#define	label_width	24

void draw_Wave_axis(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t value_min, int16_t value_max){
/*
	*u8g2		u8g2 pointer
	x			wave x-position
	y			wave y-position
	width		wave area width
	height		wave area height
	value_min	min wave value
	value_max	max wave value
*/
	float 		norm_gain = (float)height/(float)(value_max-value_min); // Normalize coefficient
	float 		norm_offset = value_min;		// Normalize offset

	// value axis
 	for(uint8_t n=0;n<=3;n++){
		draw_Value_xs(u8g2, x, (int)(y+height-norm_gain*(float)(value_max-value_min)/3*n-norm_offset-font_height), label_width, 8, (int)((float)(value_max-value_min)/3*n+value_min), 2, 1, 1, "");
	}


}

void draw_Wave(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t value_min, int16_t value_max, int16_t *value, uint16_t index){
/*
	*u8g2		u8g2 pointer
	x			wave x-position
	y			wave y-position
	width		wave area width
	height		wave area height
	value_min	min wave value
	value_max	max wave value
	*value		wave value array
				!! lrnght must be 128
	index  		newest value index
*/
	float 		norm_gain = (float)height/(float)(value_max-value_min); // Normalize coefficient
	float 		norm_offset = value_min;		// Normalize offset
	uint8_t		norm_value[128];

	uint16_t	n_data = 128;

	u8g2_SetDrawColor(u8g2, 0); // erase color
	u8g2_DrawBox(u8g2, x+label_width, y, width, height+1 );

	u8g2_SetDrawColor(u8g2, 1); // default color
	for(uint16_t n=0;n<width-label_width;n++){
		// Normalize value for plot
		if( value[(n+index)%n_data] <= value_min){
			norm_value[n] = 0;
		}else if( value[(n+index)%n_data] >= value_max){
			norm_value[n] = height;
		}else{
			norm_value[n] = norm_gain*(value[(n+index)%n_data] - norm_offset);
		}

		// plot point
		if( n == 0 ){
			u8g2_DrawPixel(u8g2, x+width-n, height-norm_value[n] + y);
		}else{
			u8g2_DrawLine(u8g2, x+width-(n-1), height-norm_value[n-1] + y, width-n + x, height-norm_value[n] + y);
		}
	}

}
