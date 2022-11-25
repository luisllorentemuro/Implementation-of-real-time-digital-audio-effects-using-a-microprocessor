/*
 * FM4_leds_sw.c
 * Cypress FM4 Funciones para acceder a los leds y al pulsador
 *  Created on: 13 jul. 2017
 *  Last modified: 2020/09/28 18:08:20
 */

//#include <assert.h>
#include "mcu.h"
#include "HAL_FM4_gpio.h"
#include "FM4_leds_sw.h"


/*------------------------------------------------- LedSwsInit -----
 *
 * Funcion: LedsSwInit(void)
 *
 * Proposito:  Esta funcion configura los GPIOs P18, PB2, P1A como salida,
 *             y escribe un '1' en todos ellos (leds apagados).
 *             También configura GPIO P20 como entrada (sw2)
 *
 * Parametros: void
 *
 * Returns:    void
 *
 *-------------------------------------------------------------------*/
 
 void LedsSwInit()
 { 
	// Azul P18
	// Deshabilita entrada analogica
	GPIO_ChannelDigAna(P18, GPIO_DIG);
	// Pin como salida
	GPIO_ChannelMode(P18,GPIO_OUTPUT);

	// Verde PB2
	// Deshabilita entrada analogica
	GPIO_ChannelDigAna(PB2, GPIO_DIG);
	// Pin como salida
	GPIO_ChannelMode(PB2,GPIO_OUTPUT);

	// Rojo P1A
	// Deshabilita entrada analogica
	GPIO_ChannelDigAna(P1A, GPIO_DIG);
	// Pin como salida
	GPIO_ChannelMode(P1A,GPIO_OUTPUT);

	// Pulsador SW2 P20
	// Pin como entrada
	GPIO_ChannelMode(P20,GPIO_INPUT);
	
	 // Leds apagados
	GPIO_ChannelWrite(P18,LED_OFF);  // Azul
	GPIO_ChannelWrite(PB2,LED_OFF);  // Verde
	GPIO_ChannelWrite(P1A,LED_OFF);  // Rojo
 }


/*------------------------------------------------- LedRGB -----
 *
 * Funcion: LedRGB (leds3)
 *
 * Proposito: Esta funcion apaga o enciende el led RGB con el color que
 *              se le pasa como argumento
 *                
 * Parametros:
 *             leds3  (IN): Puede tomar uno de los siguientes valores:
 *                           OFF, RED, GREEN, BLUE, 
 *                           YELLOW, MAGENTA, CYAN, WHITE
 *
 * Returns:    void
 * 
 * Nota: leds3  (IN): los 3 bits menos significativos codifican
 *                          el estado ON/OFF (1/0) de los leds:
 *                           bit->     2     1      0
 *                           led->    ROJO VERDE AZUL
 *
 *-------------------------------------------------------------------*/

void LedRGB(const rgb_color_t leds3)
{   GpioPinState_t led;
	//assert(leds3<(1<<MAX_LEDS));
	// Led Azul P18
	led=(leds3&(1<<0))?LED_ON:LED_OFF;
	GPIO_ChannelWrite(P18,led);  // Azul
    // Led Verde PB2	
	led=(leds3&(1<<1))?LED_ON:LED_OFF;  
	GPIO_ChannelWrite(PB2,led);  // Verde
    // Led Rojo P1A	  
	led=(leds3&(1<<2))?LED_ON:LED_OFF;
	GPIO_ChannelWrite(P1A,led);  // Rojo
}

/*------------------------------------------------- LedONOFF -----
 *
 * Funcion: LedONOFF (led, encendido)
 *
 * Proposito: Esta funcion controla los leds (RGB) de la placa
 *                
 * Parametros: led       (IN): Led a controlar (ROJO VERDE AZUL)
 *             encendido (in): LED_ON/LED_OFF encendido/apagado del led
 *
 * Returns:    void
 *
 *-------------------------------------------------------------------*/
void LedONOFF(const Leds_t led, const GpioPinState_t encendido)
{   
	switch (led){
	// Led Azul P18
		case LED_AZUL : GPIO_ChannelWrite(P18,encendido);  // Rojo;
		break;
    // Led Verde PB2	  
		case LED_VERDE : GPIO_ChannelWrite(PB2,encendido);  // Rojo;
		break;
    // Led Rojo P1A	  
		case LED_ROJO : GPIO_ChannelWrite(P1A,encendido);  // Rojo;
		break;
		default: ;//assert(0);
	}
}
