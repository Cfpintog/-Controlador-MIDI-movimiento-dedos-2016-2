#include "soc-hw.h"

uart_t  *uart0  = (uart_t *)   0x20000000;
timer_t *timer0 = (timer_t *)  0x30000000;
gpio_t  *gpio0  = (gpio_t *)   0x40000000;
//uart_t  *uart1  = (uart_t *) 0x20000000;
spi_t   *spi0   = (spi_t *)    0x50000000;
i2c_t   *i2c0   = (i2c_t *)    0x60000000;

uint8_t v;
isr_ptr_t isr_table[32];

void prueba()
{
	   uart0->rxtx=30;
	   timer0->tcr0 = 0xAA;
	   spi0->rxtx=1;
	   spi0->cs=3;
	   spi0->divisor=4;
	   i2c0->rxtx=5;
	   i2c0->divisor=5;

}
void tic_isr();

/***************************************************************************
 * IRQ handling
 */
void isr_null()
{
}

void irq_handler(uint32_t pending)
//{ if (pending==0xFFFFFFFD)


{
		uart_putchar(CTRL_CH);//0xB0
		uart_putchar(VOL_CH);//0x07
		uart_putchar(v);
//		pending=0xFFFFFFFF;
			
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN |TIMER_AR | TIMER_IRQEN;

	//int i;	
	//for(i=0; i<32; i++) {
	//	if (pending & 0x01) (*isr_table[i])();
	//	pending >>= 1;

	//}
}

void isr_init()
{
	int i;
	for(i=0; i<32; i++)
		isr_table[i] = &isr_null;
}

void isr_register(int irq, isr_ptr_t isr)
{
	isr_table[irq] = isr;
}

void isr_unregister(int irq)
{
	isr_table[irq] = &isr_null;
}

/***************************************************************************
 * TIMER Functions
 */
void msleep(uint32_t msec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

void nsleep(uint32_t nsec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000000)*nsec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


uint32_t tic_msec;

void tic_isr()
{
	tic_msec++;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

void tic_init()
{
	tic_msec = 0;
	// Setup timer0.0
	timer0->compare0 = (FCPU/1000)*210;
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN |TIMER_AR | TIMER_IRQEN;
}

/***************************************************************************
 * GPIO Functions
*/
char gpio_get()
{
return gpio0->gpio_in;
}


char gpio_dir_get()
{
return gpio0->gpio_dir;
}

void gpio_dir_set(char g)
{
	gpio0->gpio_dir=g;
}



/***************************************************************************
 * UART Functions
 */
void uart_init()
{
	//uart0->ier = 0x00;  // Interrupt Enable Register
	//uart0->lcr = 0x03;  // Line Control Register:    8N1
	//uart0->mcr = 0x00;  // Modem Control Register

	// Setup Divisor register (Fclk / Baud)
	//uart0->div = (FCPU/(57600*16));
}

char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}
/***************************************************************************
 * SPI Functions
 */
void spi_init()
{		
}

void spi_putchar0()
{
	while(spi0->run == 1);
	spi0->cs = 0;
	spi0->rxtx = 0x00;
}
void spi_putchar(uint32_t c)
{
	while(spi0->run == 1);
	spi0->rxtx = c;
			
}
char spi_getchar()
{
	while(spi0->run == 1);

	return spi0->rxtx;	
}
