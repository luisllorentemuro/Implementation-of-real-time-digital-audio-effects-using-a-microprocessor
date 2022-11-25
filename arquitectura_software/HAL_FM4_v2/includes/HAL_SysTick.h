/** \file HAL_SysTick.h
* A brief file description.
* Created on:    2021/10/01
* Last modified:
*/

#ifndef _HAL_SYSTICK_H_
#define _HAL_SYSTICK_H_

#include <stdint.h>
#include "mcu.h"
#include "HAL_SysTick.h"


/**
 * @brief   Configura System Tick en modo encuesta
 * @details Inicializa System Timer en modo `free-running`, generando eventos periodicamente.
 * @param [in]  ticks  Número de ticks entre dos eventos.
 * @return  0  Ejecución exitosa.
 * @return  1  Fello en la ejecución.
 * @note    Da valor a los registros SysTick->LOAD y SysTick->CTRL.
 *          SysTick->CTRL se configura con:
 *                  CLKSOURCE = 1 (HCLK)
 *                  ENABLE = 1
 */
uint32_t SysTick_Init(uint32_t ticks);

/**
 *
 * @brief   Comprueba si ha habido overflow en SysTick
 *
 * @return  0  No ha habido overflow. (COUNTFLAG=0)
 * @return  1  Ha habido overflow. (COUNTFLAG=1)
 */
uint32_t SysTick_ChkOvf(void);


#endif  /* _HAL_SYSTICK_H_ */
