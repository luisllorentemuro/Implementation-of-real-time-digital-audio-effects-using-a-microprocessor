/*
 * FM4_leds_sw.h
 * Cypress FM4 Funciones para acceder a los leds y al pulsador
 *  Created on: 13 jul. 2017
 *  Last modified: 2020/09/28 13:56:19
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "HAL_FM4_gpio.h"


/**
* Define los leds disponibles en la placa
*/
typedef enum Leds_enu {
            LED_AZUL=0x18,   /*< Led AZUL  GPIO pin 18  */
            LED_VERDE=0xB2,  /*< Led VERDE GPIO pin B2  */
            LED_ROJO=0x1A,   /*< Led AZUL  GPIO pin 1A  */
            MAX_LEDS=3   /*< Número de leds  */
} Leds_t;
/**
* Defines the leds state
*/
#define LED_ON  (GPIO_LOW)
#define LED_OFF (GPIO_HIGH)
/**
 * * Defines RGB Colors
 */
typedef enum rgb_color {
            OFF=0,     /*< Apagado  */
            RED=4,     /*< Rojo  */
            GREEN=2,   /*< Verde  */
            BLUE=1,    /*< Azul */
            YELLOW=6,  /*< Amarillo */
            MAGENTA=5, /*< Magenta */
            CYAN=3,    /*< Cian */
            WHITE=7,   /*< Blanco */
            MAX_COLORS=8   /*< Número de leds  */
} rgb_color_t;

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
 
 void LedsSwInit(void);

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

//void LedRGB(unsigned leds3);
void LedRGB(const rgb_color_t  leds3);

/*------------------------------------------------- LedONOFF -----
 *
 * Funcion: LedONOFF (led, encendido)
 *
 * Proposito: Esta funcion controla 1 led (led RGB) de la placa
 *                
 * Parametros: led       (IN): Led a controlar (ROJO VERDE AZUL)
 *             encendido (in): 1/0 encendido/apagado del led
 *
 * Returns:    void
 *
 *-------------------------------------------------------------------*/
void LedONOFF(const Leds_t led, const GpioPinState_t encendido);

#endif /* LEDS_H_ */
