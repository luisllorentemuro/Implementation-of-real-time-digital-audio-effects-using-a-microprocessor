/** @file efectos.h
*   @brief Interfaz pública del módulo `efectos de sonido` contiene los tipos y las funciones  
*   necesarias para el manejo de los efectos de sonido. 
* Created on:    2022/07/11
* Last modified: 2022/07/14 19:28:36
*/
#ifndef _EFECTOS_H_
#define _EFECTOS_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include "efecto_none.h"
#include "efecto_mute.h"
#include "efecto_atenuacion.h"
#include "efecto_delay.h"
#include "efecto_overdrive.h"
#include "efecto_distortion.h"
#include "efecto_fuzz.h"
/******************************************************************************
* Module Typedefs
*******************************************************************************/
/**
 * Enumeración de los efectos implementados
 */
typedef enum efectos_enu { EFECTO_NONE,         /**< Efecto deshabilitado (bypass) */
                           EFECTO_MUTE,         /**< Efecto mute */
                           EFECTO_ATENUACION,   /**< Efecto atenuación */
                           EFECTO_DELAY,        /**< Efecto delay */
                           EFECTO_OVERDRIVE,    /**< Efecto overdrive */
                           EFECTO_DISTORTION,   /**< Efecto distortion */
                           EFECTO_FUZZ,         /**< Efecto fuzz */
                           } efectos_enu_t;
/**
 * Estructura que contiene la configuración y los elementos internos de un efecto
 */
typedef struct efecto_st efecto_t;
/******************************************************************************
* Function Prototypes
*******************************************************************************/
efecto_t *efecto_create(efectos_enu_t efecto);
void efecto_destroy(efecto_t * efecto);
void efecto_update(efecto_t *efecto, void *params);
int16_t efecto_apply(efecto_t *efecto, int16_t sample);

#endif  /* _EFECTOS_H_ */ 
