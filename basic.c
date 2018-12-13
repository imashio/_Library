/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"

__IO uint32_t DelayCnt;
uint32_t Cnt_ms;
uint32_t Cnt_us;
uint32_t Cnt_100ns;


// delay
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


// Count character length
int StrLength(const char *s){
    uint8_t n = 0;
    while (*s++ != '\0')
        n++;
    return (n);
}


// flag
unsigend int    flag=0;

void set_flag(){
    flag = 1;
}

unsigned int read_flag(){
    return flag;
}
