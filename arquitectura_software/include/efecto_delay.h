/** \file efecto_delay.h
*   @brief Interfaz pública del efecto de sonido simple_dist. 
* Created on:    2022/07/11
* Last modified: 2022/07/14 20:01:44
*/
#ifndef _EFECTO_DELAY_H_
#define _EFECTO_DELAY_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
/******************************************************************************
* Module Typedefs
*******************************************************************************/
/**
 * Estructura que contiene los parámetros del efecto delay
 */
typedef struct efecto_delay_st{
    int32_t gain;            /**< Cantidad de delay (>0) en formato <16,15>*/ 
} efecto_delayparams_t;

#endif  /* _EFECTO_DELAY_H_ */ 

