
// get string length
int StrLength(const char *s);

// substring
int subStr( char *str_out, const char *str_in, unsigned int pos, unsigned int len );

// SYSTICK delay (DO NOT USE with intteruput)
void delayInit(void);
void delay_us(uint32_t);
void delay_ms(uint32_t);

