#ifndef SPIKEHW_H
#define SPIKEHW_H

#define PROMSTART 0x00000000
#define RAMSTART  0x00000800
#define RAMSIZE   0x400
#define RAMEND    (RAMSTART + RAMSIZE)

#define RAM_START 0x40000000
#define RAM_SIZE  0x04000000

#define FCPU      100000000

#define UART_RXBUFSIZE 32

#define DO_3	   	0x30  //do  3ra octava
#define RE_3	 	0x32  //re  3ra octava
#define MI_3		0x34  //mi  3ra octava
#define FA_3		0x35  //fa  3ra octava
#define SOL_3		0x37  //sol 3ra octava
#define LA_3		0x39  //la  3ra octava
#define SI_3		0x3B  //si  3ra octava
#define NOTE_ON 	0x90  //nota on canal 1
#define VEL_ON 		0x40  //velocidad de nota 64
#define VEL_OFF		0x00  //apagado de nota
#define CTRL_CH 	0xB0  //control change canal 1
#define VOL_CH 		0x07  //cambio de volumen



/****************************************************************************
 * Types
 */
typedef unsigned int  uint32_t;    // 32 Bit
typedef signed   int   int32_t;    // 32 Bit

typedef unsigned char  uint8_t;    // 8 Bit
typedef signed   char   int8_t;    // 8 Bit

/****************************************************************************
 * Interrupt handling
 */
typedef void(*isr_ptr_t)(void);

void     irq_enable();
void     irq_disable();
void     irq_set_mask(uint32_t mask);
uint32_t irq_get_mak();

void     isr_init();
void     isr_register(int irq, isr_ptr_t isr);
void     isr_unregister(int irq);

/****************************************************************************
 * General Stuff
 */
void     halt();
void     jump(uint32_t addr);


/****************************************************************************
 * Timer
 */
#define TIMER_EN     0x08    // Enable Timer
#define TIMER_AR     0x04    // Auto-Reload
#define TIMER_IRQEN  0x02    // IRQ Enable
#define TIMER_TRIG   0x01    // Triggered (reset when writing to TCR)

typedef struct {
	volatile uint32_t tcr0;
	volatile uint32_t compare0;
	volatile uint32_t counter0;
	volatile uint32_t tcr1;
	volatile uint32_t compare1;
	volatile uint32_t counter1;
} timer_t;

void msleep(uint32_t msec);
void nsleep(uint32_t nsec);

void prueba();
void tic_init();


/***************************************************************************
 * GPIO0
 */
typedef struct {
	volatile uint32_t gpio_in;//0x00	
	volatile uint32_t gpio_o;//0x04
	volatile uint32_t gpio_dir;//0x08
	
} gpio_t;
char gpio_get();



char gpio_dir_get();

void gpio_dir_set(char g);

/***************************************************************************
 * UART0
 */
#define UART_DR   0x01                    // RX Data Ready
#define UART_ERR  0x02                    // RX Error
#define UART_BUSY 0x10                    // TX Busy

typedef struct {
   volatile uint32_t ucr;
   volatile uint32_t rxtx;
} uart_t;

void uart_init();
void uart_putchar(char c);
void uart_putstr(char *str);
char uart_getchar();

/***************************************************************************
 * SPI0
 */

typedef struct {
   volatile uint32_t rxtx; 	//0x00
   volatile uint32_t run;	//0x04
   volatile uint32_t cs;	//0x08
   volatile uint32_t divisor;	//0x0c
    } spi_t;

void spi_init();
void spi_putchar0();
void spi_putchar(uint32_t c);
char spi_getchar();

/***************************************************************************
 * I2C0
 */

typedef struct {
   volatile uint32_t rxtx;
   volatile uint32_t divisor;
} i2c_t;



/***************************************************************************
 * Pointer to actual components
 */

extern uint8_t v;
extern timer_t  *timer0;
extern uart_t   *uart0; 
extern gpio_t   *gpio0; 
extern uint32_t *sram0; 

#endif // SPIKEHW_H
