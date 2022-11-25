/** @file efectos_int.h
*   @brief Interfaz ptivada del módulo `efectos de sonido` contiene los tipos y las funciones  
*   necesarias para el manejo de los efectos de sonido. 
* Created on:    2022/07/11
* Last modified: 2022/07/14 19:57:28
*/
#ifndef _EFECTOS_INT_H_
#define _EFECTOS_INT_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include "efectos.h"                   /**< Efectos de sonido interfaz pública*/
#include "efecto_none_int.h"           /**< Efecto deshabilitado (bypass) interfaz privada*/
#include "efecto_mute_int.h"           /**< Efecto mute interfaz privada*/
#include "efecto_atenuacion_int.h"     /**< Efecto atenuación interfaz privada*/
#include "efecto_delay_int.h"          /**< Efecto delay interfaz privada*/
#include "efecto_overdrive_int.h"      /**< Efecto overdrive interfaz privada*/
#include "efecto_distortion_int.h"     /**< Efecto distortion interfaz privada*/
#include "efecto_fuzz_int.h"           /**< Efecto fuzz interfaz privada*/

/**
 * Definición de la estructura que contiene la configuración y 
 *   los elementos internos de un efecto
 */
struct efecto_st {
    efectos_enu_t efecto;       /**< Tipo de efecto */
    void *internals;            /**< Puntero a los elementos internos del efecto */
    void *params;               /**< Puntero a los parámetros del efecto */
};

#endif  /* _EFECTOS_INT_H_ */ 
