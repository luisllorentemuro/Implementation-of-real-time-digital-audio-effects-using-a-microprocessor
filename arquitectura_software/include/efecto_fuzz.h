/** \file efecto_fuzz.h
*   @brief Interfaz pública del efecto de sonido fuzz. 
* Created on:    2022/07/11
* Last modified: 2022/07/14 20:01:44
*/
#ifndef _EFECTO_FUZZ_H_
#define _EFECTO_FUZZ_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <math.h>
#include "fixedpoint.h"
/******************************************************************************
* Module Typedefs
*******************************************************************************/
/**
 * Estructura que contiene los parámetros del efecto fuzz
 */
typedef struct efecto_fuzz_st{
    int16_t gain;            /**< Cantidad de distosión (>0) en formato <16,15>*/ 
    int16_t mix;             /**< Mix entre la señal original y la distorsionada en formato <16,15> (0<mix<1) (1=solo señal distorsionada)*/
	int16_t max_abs_x;       /**< Mix entre la señal original y la distorsionada en formato <16,15> (0<mix<1) (1=solo señal distorsionada)*/
	int16_t max_abs_y;       /**< Mix entre la señal original y la distorsionada en formato <16,15> (0<mix<1) (1=solo señal distorsionada)*/
	int16_t max_abs_z;       /**< Mix entre la señal original y la distorsionada en formato <16,15> (0<mix<1) (1=solo señal distorsionada)*/
} efecto_fuzzparams_t;

#endif  /* _EFECTO_FUZZ_H_ */ 
