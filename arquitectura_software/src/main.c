#include <stdint.h>
#include "mcu.h"
#include "FM4_WM8731.h"
#include "HAL_FM4_i2s.h"
#include "HAL_FM4_gpio.h"
#include "FM4_leds_sw.h"
#include "pulsaciones.h"
#include "HAL_FM4_dtimer.h"
#include "HAL_SysTick.h"
#include "fixedpoint.h"

#define FM4_sw2 P20

uint8_t g_contador = 0;

int32_t main(void)
{
 
	//Inicializaci�n de variables globales

	//Variables locales

	uint32_t ticks = SystemCoreClock/1000;	// Entrada a SysTick para generar el evento cada 1ms
	uint32_t overflow;											// Almacena si ha habido overflow en SysTick o no
	uint8_t salida;												// Almacena la pulsacion que hagamos en el pin de la placa
	GpioPinState_t pulsacion;
	
	// Configuraci�n de perif�ricos y Codec

	LedsSwInit();
	GPIO_ChannelDigAna(P10,GPIO_DIG);
	GPIO_ChannelMode(P10,GPIO_OUTPUT);

	// Inicializaci�n del SysTick
	SysTick_Init(ticks);

	// Inicializaci�n del I2C, Codec e I2S.

	FM4_WM8731_init (FS_8000_HZ,               // Sampling rate (sps)
								WM8731_LINE_IN,            // Audio input port
								WM8731_HP_OUT_GAIN_0_DB,   // Output headphone jack Gain (dB)
								WM8731_LINE_IN_GAIN_0_DB); // Line-in input gain (dB)

	// Puesta en marcha de I2S
	I2S_start();
	// Habilita interrupci�n de I2S
	NVIC_EnableIRQ(PRGCRC_I2S_IRQn);

	// Inicializaci�n de las LUTs
	fixedpoint_init();
	
	uint8_t contador = 0;
	while(1)
	{  

		overflow = SysTick_ChkOvf();													// Encuesta a SysTick, ha habido overflow?
		if(overflow == 1)																			// Indicador de que ha pasado 1ms
		{	
			GPIO_ChannelToggle(P10);														// Cambiamos el valor del Pin10
			pulsacion = (GPIO_ChannelRead(FM4_sw2)==GPIO_LOW)?GPIO_HIGH:GPIO_LOW;
			salida = pulsaciones(pulsacion);
								
			if(salida == 1)		//Pulsacion corta
			{
				contador++;
				if(contador >= 7)	//Control desbordamiento
				{
					contador = 0;
				}
			}
			else if(salida == 2)	//Pulsacion larga
			{
					g_contador = contador;
					contador = 0;
			}

			if(contador == 0) 
			{
				LedRGB(OFF); // EFECTO_NONE
			}
			else if(contador == 1)
			{
				LedRGB(RED); // EFECTO_MUTE
			}
			else if(contador == 2)
			{
				LedRGB(GREEN); // EFECTO_ATENUACION
			}
			else if(contador == 3)
			{
				LedRGB(BLUE); // EFECTO_DELAY
			}
			else if(contador == 4)
			{
				LedRGB(CYAN); // EFECTO_OVERDRIVE
			}
			else if(contador == 5)
			{
				LedRGB(YELLOW); // EFECTO_DISTORTION
			}
			else if(contador == 6)
			{
				LedRGB(MAGENTA); // EFECTO_FUZZ
			}
		}
	}
}
	



