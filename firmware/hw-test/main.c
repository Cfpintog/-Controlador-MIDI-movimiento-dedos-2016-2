#include "soc-hw.h"

char glob[] = "Global";


//Tabla de valores GPIO		| meñique | anular | corazón | índice | (1 flexión, 0 extendido)
#define DO  0x01	      //     0	      0         0        1
#define RE  0x02	      //     0	      0         1        0
#define MI  0x03	      //     0        0         1        1
#define FA  0x04	      //     0        1         0        0
#define SOL 0x05	      //     0        1         0        1
#define LA  0x06	      //     0        1         1        0
#define SI  0x07	      //     0        1         1        1

//Comunicación MIDI
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


volatile uint32_t *p;
volatile uint8_t *p2;
extern uint32_t tic_msec;

	uint8_t vel;	  //señal de velocidad de nota
	uint8_t x;     //señal tono
	uint8_t y;	//señal velocidad 
//	extern uint8_t v;

int nota (int cmb); //Retorna la nota a partir de la combinación del guante
int speed (int comb);	    //Retorna la velocidad a partir de la combinación		




int main()
	{//uint8_t vol;     //señal de volumen transmitida en UART
	uint8_t tn;
	uint8_t vel;
	//uint8_t v;   	  //señal recibida de spi (conversor)
	uint8_t n;   //señal recibida de gpio (fototransistor)
	irq_set_mask(0x02);
	irq_enable();
		
	tic_init();//funcion timer interrupcion
		for(;;)
		{//lectura de datos
		//conversor
		spi_putchar0();
		v=spi_getchar();

		//fototransistores
		n = gpio_get();	
		
		
		//adecuacion señales tono y velocidad		
		tn=nota(n);
		vel=speed(n);
	
		
		//Transmisión de mensaje MIDI
		//Volumen
		//uart_putchar(CTRL_CH);//0xB0
		//uart_putchar(VOL_CH);//0x07
		//uart_putchar(v);
		msleep(10);
		//Tipo de nota
		
		uart_putchar(NOTE_ON);//0x90
		uart_putchar(tn);//
		uart_putchar(vel);
		msleep(100);
		
		}
	}



	int nota (int cmb)
		{
		if (cmb==DO)
			{
			x= DO_3;
			}
		else if (cmb==RE)
			{
			x=RE_3;
			}
		else if (cmb==MI)
			{
			x=MI_3;
			}
		else if (cmb==FA)
			{
			x=FA_3;
			}
		else if (cmb==SOL)
			{
			x=SOL_3;
			}
		else if (cmb==LA)
			{
			x=LA_3;
			}
		else if (cmb==SI)
			{
			x=SI_3;
			}
		else	
			{
			x=0;
			}
		return x;
		}

	int speed(int comb)
		{
		if(comb==DO || comb==RE || comb==MI || comb==FA || comb==SOL || comb==LA || comb==SI)
			{
			 y=VEL_ON;
			}
		else
			{
			y=VEL_OFF;
			}
		return y;
		}




