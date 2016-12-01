#include "soc-hw.h"

char glob[] = "Global";


//Tabla de valores GPIO		| meñique 0x02 | anular 0x04 | corazón 0x01 | índice 0x08 | (0 flexión, 1 extendido)
#define DO  0x0A	      //     1	      0         0        1
#define RE  0x0F	      //     1	      1         1        1
#define MI  0x00	      //     0        0         0        0
#define FA  0x08	      //     0        0         0        1
#define SOL 0x0D	      //     0        1         1        1
#define LA  0x09	      //     0        0         1        1
#define SI  0x02	      //     1        0         0        0

//Comunicación MIDI
#define DO_3	   	0x24  //do  3ra octava
#define RE_3	 	0x26  //re  3ra octava
#define MI_3		0x28  //mi  3ra octava
#define FA_3		0x29  //fa  3ra octava
#define SOL_3		0x2B  //sol 3ra octava
#define LA_3		0x2D  //la  3ra octava
#define SI_3		0x2F //si  3ra octava
#define NOTE_ON 	0x90  //nota on canal 1
#define VEL_ON 		0x40 //velocidad de nota 64
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
	uint8_t n_0;
	
	//uint8_t v;   	  //señal recibida de spi (conversor)
	uint8_t n;   //señal recibida de gpio (fototransistor)
	//activación de interrupciones
	irq_set_mask(0x02);
	irq_enable();
	
	n_0=gpio_get();//creación variable antigua de gpio
	tic_init(); //funcion timer interrupcion
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

		//cambio de nota sin repetir.
			if(n_0==n)
				{
				}
			else
				{n_0=n;
				uart_putchar(NOTE_ON);//0x90
				uart_putchar(tn);//transmisión tono
				uart_putchar(vel);//transmisión velocidad
				}
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




