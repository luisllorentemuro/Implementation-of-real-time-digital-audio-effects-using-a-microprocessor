/** \file efecto_distortion.h
*   @brief Interfaz pública del efecto de sonido simple_dist. 
* Created on:    2022/07/11
* Last modified: 2022/07/14 20:01:44
*/
#ifndef _EFECTO_DISTORTION_H_
#define _EFECTO_DISTORTION_H_
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
 * Estructura que contiene los parámetros del efecto distortion
 */
typedef struct efecto_distortion_st{
    int32_t gain;            /**< Cantidad de distosión (>0) en formato <16,15>*/ 
    int16_t mix;            /**< Mix entre la señal original y la distorsionada en formato <16,15> (0<mix<1) (1=solo señal distorsionada)*/
} efecto_distortionparams_t;

#endif  /* _EFECTO_DISTORTION_H_ */ 
