/*
 * pulsaciones.h
 *
 */
 
 /*

#ifndef PULSACIONES_H_
#define PULSACIONES_H_
#include <stdint.h>

uint8_t pulsaciones(uint8_t pulsado);
uint8_t pulsaciones2(uint8_t pulsado);

*/

//#endif /* PULSACIONES_H_ */


/*
 * pulsaciones.h
 *
 */

#ifndef PULSACIONES_H_
#define PULSACIONES_H_
#include <stdint.h>
#include "HAL_FM4_gpio.h"

/*
* uint8_t pulsaciones(estado_gpio)
* 
* Prop�sito: detecta los patrones pulsaci�n larga y
*             pulsaci�n corta en el GPIO que se le
*             pasa como argumento.
*
* Par�metros: estado_gpio (IN)  GPIO_LOW/GPIO_HIGH
*
* Returns:	0 -> si no hay pulsacion
* 		1 -> pulsaci�n corta
* 		2 -> pulsaci�n larga
* 			
*/
uint8_t pulsaciones (GpioPinState_t estado_gpio);


#endif /* PULSACIONES_H_ */

