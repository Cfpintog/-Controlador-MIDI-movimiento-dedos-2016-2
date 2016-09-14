/**
* 
*/

#include "soc-hw.h"

inline void writeint(uint32_t val)
{
	uint32_t i, digit;

	for (i=0; i<8; i++) {
		digit = (val & 0xf0000000) >> 28;
		if (digit >= 0xA) 
			uart_putchar('A'+digit-10);
		else
			uart_putchar('0'+digit);
		val <<= 4;
	}
}



char glob[] = "Global";

volatile uint32_t *p;
volatile uint8_t *p2;
volatile uint32_t i;

extern uint32_t tic_msec;

int main()
{
spi_init(14);
i=600;
spi_putchar(i,2);
spi_init(230);
spi_putchar(i,4);

/*gpio_dir_set(0x3A);
gpio_set(0x12);*/
}
