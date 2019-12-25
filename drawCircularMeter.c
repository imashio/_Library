/*
 * CircularMeter.c
 *
 *  Created on: Jan 28, 2018
 *      Author: imashio
 */
#include "u8g2.h"		// graphic display library
#include <math.h>


int16_t	circle_value_min;
int16_t	circle_value_max;

uint8_t circle_offset_x;
uint8_t circle_offset_y;
uint8_t circle_r;
uint8_t circle_tick_length;

uint8_t	circle_tick_num;
uint8_t	circle_dot_num;
int16_t	circle_rad_offset;
int16_t	circle_rad_tick;
int16_t	circle_rad_dot;
int16_t	circle_rad_max;
int8_t	circle_dir; // 1:Clockwise , -1:Counter-Clockwise

int16_t last_deg;

draw_CircularMeter_Init(uint8_t x, uint8_t  y, uint8_t  r, uint8_t tick_length, int16_t rad_offset, int16_t rad_max, uint8_t tick_num, uint8_t dot_num, int8_t dir, int16_t value_min, int16_t value_max){
  circle_offset_x = x;
  circle_offset_y = y;
  circle_r = r;
  circle_tick_length = tick_length;
  circle_rad_offset = rad_offset;
  circle_rad_max = rad_max;
  circle_tick_num = tick_num;
  circle_dot_num = dot_num;
  circle_rad_tick = rad_max / tick_num;
  circle_rad_dot = rad_max / dot_num;
  circle_dir = dir;
  circle_value_min = value_min;
  circle_value_max = value_max;
}


draw_CircularMeter(u8g2_t *u8g2, int16_t value){
	int16_t deg;
	int16_t circle_x;
	int16_t circle_y;
	int16_t	circle_tick1_x;
	int16_t	circle_tick1_y;
	int16_t	circle_tick2_x;
	int16_t	circle_tick2_y;

	if( value < circle_value_min ){
		value = circle_value_min;
	}else if( value > circle_value_max ){
		value = circle_value_max;
	}
	deg = circle_rad_max * (double)(value - circle_value_min)/(circle_value_max-circle_value_min);

	// erace circle
	u8g2_SetDrawColor(u8g2, 0); // erase color
	u8g2_DrawDisc(u8g2, circle_offset_x, circle_offset_y, circle_r, U8G2_DRAW_ALL);

	// draw center disc
	u8g2_SetDrawColor(u8g2, 1); // default color
	u8g2_DrawDisc(u8g2, circle_offset_x, circle_offset_y, 1, U8G2_DRAW_ALL);

	// draw tick
	for(uint8_t n=0; n<=circle_tick_num; n++){
	  circle_tick1_x = + circle_r * cos( circle_dir*(double)( circle_rad_tick*n - circle_rad_offset )/180.0*M_PI );
	  circle_tick1_y = - circle_r * sin( circle_dir*(double)( circle_rad_tick*n - circle_rad_offset )/180.0*M_PI );
	  circle_tick2_x = +(circle_r-circle_tick_length) * cos( circle_dir*(double)( circle_rad_tick*n - circle_rad_offset )/180.0*M_PI );
	  circle_tick2_y = -(circle_r-circle_tick_length) * sin( circle_dir*(double)( circle_rad_tick*n - circle_rad_offset )/180.0*M_PI );
	  u8g2_DrawLine(u8g2, circle_offset_x+circle_tick1_x, circle_offset_y+circle_tick1_y, circle_offset_x+circle_tick2_x, circle_offset_y+circle_tick2_y);
	}

	// draw dots
	for(uint8_t n=0; n<=circle_dot_num; n++){
	  circle_tick1_x = + circle_r * cos( circle_dir*(double)( circle_rad_dot*n - circle_rad_offset )/180.0*M_PI );
	  circle_tick1_y = - circle_r * sin( circle_dir*(double)( circle_rad_dot*n - circle_rad_offset )/180.0*M_PI );
	  u8g2_DrawPixel(u8g2, circle_offset_x+circle_tick1_x, circle_offset_y+circle_tick1_y);
	}

	// draw indicator
	circle_x = + (circle_r-1) * cos( circle_dir*(double)( deg		- circle_rad_offset )/180.0*M_PI );
	circle_y = - (circle_r-1) * sin( circle_dir*(double)( deg		- circle_rad_offset )/180.0*M_PI );
	u8g2_DrawLine(u8g2, circle_offset_x, circle_offset_y, circle_offset_x+circle_x, circle_offset_y+circle_y);

	last_deg = deg;
}

