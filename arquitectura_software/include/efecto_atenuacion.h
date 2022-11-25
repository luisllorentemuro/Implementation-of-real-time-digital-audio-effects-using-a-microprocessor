/** \file efecto_atenuacion.h
*   @brief Interfaz pública del efecto de sonido ganancia. 
* Created on:    2022/07/13
* Last modified: 2022/07/14 20:00:07
*/

#ifndef _EFECTO_ATENUACION_H_
#define _EFECTO_ATENUACION_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
/******************************************************************************
* Module Typedefs
*******************************************************************************/
/**
 * Estructura que contiene los parámetros del efecto atenuación
 */
typedef struct efecto_atenuacion_st{
      int16_t atenuacion;       /**< Atenuación en formato <16,15>*/
  } efecto_atenuacionparams_t;

#endif  /* _EFECTO_ATENUACION_H_ */ 
