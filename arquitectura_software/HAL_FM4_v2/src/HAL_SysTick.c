/** \file HAL_SysTick.c
* A brief file description.
* Created on:    2021/10/01
* Last modified:
*/

#include "mcu.h"
#include "HAL_SysTick.h"




/**
 *
 * @brief   Configura System Tick en modo encuesta
 * @details Inicializa System Timer en modo `free-running`generando eventos periodicamente.
 * @param [in] ticks  Número de ticks entre dos eventos.
 * @return  0  Ejecución exitosa.
 * @return  1  Fello en la ejecución.
 * @note    Da valor a los registros SysTick->LOAD y SysTick->CTRL.
 *          SysTick->CTRL se configura con:
 *                  CLKSOURCE = 1 (HCLK)
 *                  ENABLE = 1
 */
uint32_t SysTick_Init(uint32_t ticks)
{
  if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
  {
    return (1UL);                                                   /* Valor de recarga invalido */
  }

  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* Guarda valor de recarga */
  SysTick->VAL   = 0UL;                                             /* Limpia timer */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk;                         /* Habilita SysTick Timer */
  return (0UL);                                                     /* Ok */
}

/**
 *
 * @brief   Comprueba si ha habido overflow en SysTick
 *
 * @return  0  No ha habido overflow. (COUNTFLAG=0)
 * @return  1  Ha habido overflow.    (COUNTFLAG=1)
 */
__INLINE  uint32_t SysTick_ChkOvf(void)
{ uint32_t overflow=0;
  if (SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk) overflow=1u;
  return overflow;
}
