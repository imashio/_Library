/*
 * drawStr.c
 *
 *  Created on: Jan 29, 2018
 *      Author: imashio
 */

#include "u8g2.h"		// graphic display library


#define	meas_label_font		u8g2_font_5x8_tf
#define	meas_label_font_b	u8g2_font_7x14B_tf
#define	meas_unit_font		u8g2_font_4x6_tf
#define	meas_unit_font_b	u8g2_font_7x14B_tf
#define	meas_value_font		u8g2_font_7x14B_tf
#define	meas_value_font_b	u8g2_font_logisoso16_tf
#define	meas_value_font_s	u8g2_font_6x10_tf
#define	meas_value_font_xs	u8g2_font_5x8_tf

#define font_width			7
#define font_width_b		10
#define font_width_s		6
#define font_width_xs		5

void draw_MeasLabelUnit(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char *name, const char *unit){
	uint8_t	str_offset;
	u8g2_SetFont(u8g2, meas_label_font);
	u8g2_DrawStr(u8g2, x, y+height-2, name );
	u8g2_SetFont(u8g2, meas_unit_font);
	str_offset = (width-1) - (StrLength(unit)*4);
	u8g2_DrawStr(u8g2, x+str_offset, y+height-2, unit );
}

void draw_MeasLabelUnit_b(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char *name, const char *unit){
	uint8_t	str_offset;
	u8g2_SetFont(u8g2, meas_label_font_b);
	u8g2_DrawStr(u8g2, x, y+height-2, name );
	u8g2_SetFont(u8g2, meas_unit_font_b);
	str_offset = (width-1) - (StrLength(unit)*7);
	u8g2_DrawStr(u8g2, x+str_offset, y+height-2, unit );
}

void draw_MeasLabel(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char *name){
	u8g2_SetFont(u8g2, meas_label_font);
	u8g2_DrawStr(u8g2, x, y+height-2, name );
}

void draw_MeasUnit(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, const char *unit){
	uint8_t	str_offset;
	u8g2_SetFont(u8g2, meas_unit_font);
	str_offset = (width-1) - (StrLength(unit)*4);
	u8g2_DrawStr(u8g2, x+str_offset, y+height-2, unit );
}

void draw_Value(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t value, uint8_t digit, uint8_t frac, uint8_t sign, const char *unit){
	int16_t int_value;
	int16_t sub_value;
	uint16_t pow10 = 1;
	uint8_t valid_digit = digit;
	uint8_t int_digit = digit-frac;
	uint8_t	str_offset;

	u8g2_SetFont(u8g2, meas_value_font);

	str_offset = (width-1) - ( StrLength(unit)*4 + ((sign!=0)+digit)*font_width + ((frac!=0)*font_width>>1) + 1 );

	// erase blank space
	u8g2_SetDrawColor(u8g2, 0); // erase color
	for( uint8_t n=int_digit-1; n>0; n-- ){
		if( value >= pow(10, n+frac) ){
			break;
		}else{
			u8g2_DrawBox(u8g2, x+str_offset, y, font_width, height );
			str_offset = str_offset + font_width;
			valid_digit--;
		}
	}
	u8g2_SetDrawColor(u8g2, 1); // default color

	// sign
	if( sign!=0 ){
		// erase previous sign
		u8g2_SetDrawColor(u8g2, 0); // erase color
		u8g2_DrawBox(u8g2, x+str_offset, y, font_width, height );
		u8g2_SetDrawColor(u8g2, 1); // default color

		if(	value < 0 ){
			u8g2_DrawStr(u8g2, x+str_offset, y+height-2, "-");
			value = -value;
			str_offset = str_offset + font_width;
		}else if( value >= 0 ){
			u8g2_DrawStr(u8g2, x+str_offset, y+height-2, "+");
			str_offset = str_offset + font_width;
		}
	}

	//int
	if( frac==0 ){
		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(value, valid_digit) );
	}else{
		pow10 = pow(10, frac);
		int_value = value / pow10;
		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(int_value, valid_digit-frac) );
		str_offset = str_offset + (valid_digit-frac)*font_width;

		u8g2_DrawStr(u8g2, x+str_offset - ( (font_width>>1)-(font_width>>2) ), y+height-2, ".");
		str_offset = str_offset + (font_width>>1);

		sub_value = int_value * pow10;
		uint8_t frac_value = value - sub_value;

		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(frac_value, frac) );
	}
}

void draw_Value_b(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t value, uint8_t digit, uint8_t frac, uint8_t sign, const char *unit){
	int16_t int_value;
	int16_t sub_value;
	uint16_t pow10 = 1;
	uint8_t valid_digit = digit;
	uint8_t int_digit = digit-frac;
	uint8_t	str_offset;

	u8g2_SetFont(u8g2, meas_value_font_b);

	str_offset = (width-1) - ( StrLength(unit)*7 + ((sign!=0)+digit)*font_width_b + ((frac!=0)*font_width_b>>1) + 1 );

	// erase blank space
	u8g2_SetDrawColor(u8g2, 0); // erase color
	for( uint8_t n=int_digit-1; n>0; n-- ){
		if( value >= pow(10, n+frac) ){
			break;
		}else{
			u8g2_DrawBox(u8g2, x+str_offset, y, font_width_b, height );
			str_offset = str_offset + font_width_b;
			valid_digit--;
		}
	}
	u8g2_SetDrawColor(u8g2, 1); // default color

	// sign
	if( sign!=0 ){
		// erase previous sign
		u8g2_SetDrawColor(u8g2, 0); // erase color
		u8g2_DrawBox(u8g2, x+str_offset, y, font_width_b, height );
		u8g2_SetDrawColor(u8g2, 1); // default color

		if(	value < 0 ){
			u8g2_DrawStr(u8g2, x+str_offset, y+height-2, "-");
			value = -value;
			str_offset = str_offset + font_width_b;
		}else if( value >= 0 ){
			u8g2_DrawStr(u8g2, x+str_offset, y+height-2, "+");
			str_offset = str_offset + font_width_b;
		}
	}

	//int
	if( frac==0 ){
		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(value, valid_digit) );
	}else{
		pow10 = pow(10, frac);
		int_value = value / pow10;
		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(int_value, valid_digit-frac) );
		str_offset = str_offset + (valid_digit-frac)*font_width_b;

		u8g2_DrawStr(u8g2, x+str_offset - ( (font_width_b>>1)-(font_width_b>>2) ), y+height-2, ".");
		str_offset = str_offset + (font_width_b>>1);

		sub_value = int_value * pow10;
		uint8_t frac_value = value - sub_value;

		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(frac_value, frac) );
	}
}


void draw_Value_s(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t value, uint8_t digit, uint8_t frac, uint8_t sign, const char *unit){
	int16_t int_value;
	int16_t sub_value;
	uint16_t pow10 = 1;
	uint8_t valid_digit = digit;
	uint8_t int_digit = digit-frac;
	uint8_t	str_offset;

	u8g2_SetFont(u8g2, meas_value_font_s);

	str_offset = (width-1) - ( StrLength(unit)*4 + ((sign!=0)+digit)*font_width_s + ((frac!=0)*font_width_s>>1) + 1 );

	// erase blank space
	u8g2_SetDrawColor(u8g2, 0); // erase color
	for( uint8_t n=int_digit-1; n>0; n-- ){
		if( value >= pow(10, n+frac) ){
			break;
		}else{
			u8g2_DrawBox(u8g2, x+str_offset, y, font_width_s, height );
			str_offset = str_offset + font_width_s;
			valid_digit--;
		}
	}
	u8g2_SetDrawColor(u8g2, 1); // default color

	// sign
	if( sign!=0 ){
		// erase previous sign
		u8g2_SetDrawColor(u8g2, 0); // erase color
		u8g2_DrawBox(u8g2, x+str_offset, y, font_width_s, height );
		u8g2_SetDrawColor(u8g2, 1); // default color

		if(	value < 0 ){
			u8g2_DrawStr(u8g2, x+str_offset, y+height-2, "-");
			value = -value;
			str_offset = str_offset + font_width_s;
		}else if( value >= 0 ){
			u8g2_DrawStr(u8g2, x+str_offset, y+height-2, "+");
			str_offset = str_offset + font_width_s;
		}
	}

	//int
	if( frac==0 ){
		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(value, valid_digit) );
	}else{
		pow10 = pow(10, frac);
		int_value = value / pow10;
		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(int_value, valid_digit-frac) );
		str_offset = str_offset + (valid_digit-frac)*font_width_s;

		u8g2_DrawStr(u8g2, x+str_offset - ( (font_width_s>>1)-(font_width_s>>2) ), y+height-2, ".");
		str_offset = str_offset + (font_width_s>>1);

		sub_value = int_value * pow10;
		uint8_t frac_value = value - sub_value;

		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(frac_value, frac) );
	}
}


void draw_Value_xs(u8g2_t *u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, int16_t value, uint8_t digit, uint8_t frac, uint8_t sign, const char *unit){
	int16_t int_value;
	int16_t sub_value;
	uint16_t pow10 = 1;
	uint8_t valid_digit = digit;
	uint8_t int_digit = digit-frac;
	uint8_t	str_offset;

	u8g2_SetFont(u8g2, meas_value_font_xs);

	str_offset = (width-1) - ( StrLength(unit)*4 + ((sign!=0)+digit)*font_width_xs + ((frac!=0)*font_width_xs>>1) + 1 );

	// erase blank space
	u8g2_SetDrawColor(u8g2, 0); // erase color
	for( uint8_t n=int_digit-1; n>0; n-- ){
		if( value >= pow(10, n+frac) ){
			break;
		}else{
			u8g2_DrawBox(u8g2, x+str_offset, y, font_width_xs, height );
			str_offset = str_offset + font_width_xs;
			valid_digit--;
		}
	}
	u8g2_SetDrawColor(u8g2, 1); // default color

	// sign
	if( sign!=0 ){
		// erase previous sign
		u8g2_SetDrawColor(u8g2, 0); // erase color
		u8g2_DrawBox(u8g2, x+str_offset, y, font_width_xs, height );
		u8g2_SetDrawColor(u8g2, 1); // default color

		if(	value < 0 ){
			u8g2_DrawStr(u8g2, x+str_offset, y+height-2, "-");
			value = -value;
			str_offset = str_offset + font_width_xs;
		}else if( value >= 0 ){
			u8g2_DrawStr(u8g2, x+str_offset, y+height-2, "+");
			str_offset = str_offset + font_width_xs;
		}
	}

	//int
	if( frac==0 ){
		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(value, valid_digit) );
	}else{
		pow10 = pow(10, frac);
		int_value = value / pow10;
		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(int_value, valid_digit-frac) );
		str_offset = str_offset + (valid_digit-frac)*font_width_xs;

		u8g2_DrawStr(u8g2, x+str_offset - ( (font_width_xs>>1)-(font_width_xs>>2) ), y+height-2, ".");
		str_offset = str_offset + (font_width_xs>>1);

		sub_value = int_value * pow10;
		uint8_t frac_value = value - sub_value;

		u8g2_DrawStr(u8g2, x+str_offset, y+height-2, u8g2_u16toa(frac_value, frac) );
	}
}

