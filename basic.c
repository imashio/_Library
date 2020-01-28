/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"

// Count character length
int StrLength(const char *s){
    uint8_t n = 0;
    while (*s++ != '\0')
        n++;
    return (n);
}

// substring
int subStr( char *str_out, const char *str_in, unsigned int pos, unsigned int len ){
    if( pos < 0 || len < 0 || len > strlen(str_in) )
        return -1;
    for( str_in += pos; *str_in != '\0' && len > 0; len-- )
        *str_out++ = *str_in++;
    *str_out = '\0';
    return 0;
}

// SYSTICK delay (DO NOT USE with intteruput)
__IO uint32_t DelayCnt;
uint32_t Cnt_ms;
uint32_t Cnt_us;
uint32_t Cnt_100ns;

void delayInit(void)
{
  uint32_t freq;
  freq = HAL_RCC_GetHCLKFreq();
  Cnt_ms = 1 * (freq/1000);
  Cnt_us = 1 * (freq/1000000);
}

void delay_us(uint32_t t_us)
{
	HAL_SYSTICK_Config(Cnt_us-1);
	DelayCnt = t_us;
	while( DelayCnt != 0 );
}

void delay_ms(uint32_t t_ms)
{
	HAL_SYSTICK_Config(Cnt_ms-1);
	DelayCnt = t_ms;
	while( DelayCnt != 0 );
}


