/*
  draw_Wavw.c

   Created on: Nov 11, 2018
       Author: imashio
 */

#include "u8g2.h"		// graphic display library

#define font_width	4
#define font_height	6
#define	label_width	24

uint8_t box_x;
uint8_t box_y;
uint8_t box_width;
uint8_t box_height;

float 		norm_gain;
int			norm_offset;

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
	box_x = x+label_width;
	box_y = y+font_height/2;
	box_width = width-label_width - 2; // '2' is Line-width
	box_height = height-font_height - 2; // '2' is Line-width

	norm_gain = (float)(box_height)/(float)(value_max-value_min); // Normalize coefficient
	norm_offset = value_min;		// Normalize offset


	// value axis
 	for(uint8_t n=0;n<=3;n++){
		draw_Value_xs(u8g2, x, (int)(box_y+box_height-norm_gain*(float)(value_max-value_min)/3*n-font_height/2 ), label_width, 8, (int)((float)(value_max-value_min)/3*n+value_min), 3, 2, 1, "");
	}
	u8g2_DrawFrame(u8g2, box_x-1, box_y-1, box_width+2, box_height+2 );
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
				!! lenghth must be 128
	index  		newest value index
*/
	uint8_t		norm_value[128];

	uint16_t	n_data = 128;

	u8g2_SetDrawColor(u8g2, 0); // erase color
	u8g2_DrawBox(u8g2, box_x, box_y, box_width, box_height );

	u8g2_SetDrawColor(u8g2, 1); // default color
	for(uint16_t n=0;n<width-label_width;n++){
		// Normalize value for plot
		if( value[(n+index)%n_data] <= value_min){
			norm_value[n] = 0;
 		}else if( value[(n+index)%n_data] >= value_max){
			norm_value[n] = norm_gain*((float)value_max - (float)norm_offset);
 		}else{
			norm_value[n] = norm_gain*((float)value[(n+index)%n_data] - (float)norm_offset);
		}

		// plot point
		if( n == 0 ){
			u8g2_DrawPixel(u8g2, box_x+box_width-n, box_y+box_height-norm_value[n]-1);
		}else{
			u8g2_DrawLine(u8g2, box_x+box_width-(n-1), box_y+box_height-norm_value[n-1]-1 , box_x+box_width-n, box_y+box_height-norm_value[n]-1);
		}
	}

}
