/** \file efectos.c
 *   @brief Módulo `efectos de sonido` contiene las funciones  
 *   necesarias para el manejo de los efectos de sonido. 
 * Created on:    2022/07/11
 * Last modified: 2022/07/14 19:52:04
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdlib.h>         /* Funciones gestión dinémica de la memoria */
#include <stdint.h>         /* Definición de tipos portables */
#include "efectos.h"        /* Interfaz pública del módulo */
#include "efectos_int.h"    /* Tipos internos del módulo */
/******************************************************************************
* Function Definitions
*******************************************************************************/
/**
 * @brief Crea un nuevo efecto de sonido.
 * @param efecto Tipo de efecto a crear.
 * @return Puntero a la estructura de datos del efecto creado.
 */
efecto_t *efecto_create(efectos_enu_t efecto)
{
    efecto_t *efecto_ptr;
    switch (efecto)
    {
    case EFECTO_NONE:
        efecto_ptr = efecto_none_create();
        break;
    case EFECTO_MUTE:
        efecto_ptr = efecto_mute_create();
        break;
    case EFECTO_ATENUACION:
        efecto_ptr = efecto_atenuacion_create();
        break;
    case EFECTO_DELAY:
        efecto_ptr = efecto_delay_create();
        break;
    case EFECTO_OVERDRIVE:
        efecto_ptr = efecto_overdrive_create();
        break;
    case EFECTO_DISTORTION:
        efecto_ptr = efecto_distortion_create();
        break;
    case EFECTO_FUZZ:
        efecto_ptr = efecto_fuzz_create();
        break;
    default:
        efecto_ptr = NULL;
    }
    return efecto_ptr;
}
/**
 * @brief Destruye un efecto de sonido.
 * @param efecto Puntero a la estructura de datos del efecto a destruir.
 */
void efecto_destroy(efecto_t *efecto)
{
    if (efecto != NULL)
    {
        if (efecto->internals != NULL)
        {
            free(efecto->internals);
        }
        efecto->internals = NULL;
        if (efecto->params != NULL)
        {
            free(efecto->params);
        }
        efecto->internals = NULL;
        free(efecto);
    }
}
/**
 * @brief Actualiza los parámetros de un efecto de sonido.
 * @param efecto Puntero a la estructura de datos del efecto a actualizar.
 * @param params Puntero a la estructura de datos con los parámetros del efecto.
 */
void efecto_update(efecto_t *efecto, void *params)
{
    switch (efecto->efecto)
    {
    case EFECTO_NONE:
        break;
    case EFECTO_MUTE:
        break;
    case EFECTO_ATENUACION:
        efecto_atenuacion_update(efecto, params);
        break;
    case EFECTO_DELAY:
        efecto_delay_update(efecto, params);
        break;
    case EFECTO_OVERDRIVE:
        break;
    case EFECTO_DISTORTION:
        efecto_distortion_update(efecto, params);
        break;
    case EFECTO_FUZZ:
        efecto_fuzz_update(efecto, params);
        break;
    default:
        break;
    }
}
/**
 * @brief Aplica un efecto de sonido a una muestra.
 * @param efecto Puntero a la estructura de datos del efecto a aplicar.
 * @param sample Muestra a aplicar el efecto.
 * @return Muestra con el efecto aplicado.
 */
int16_t efecto_apply(efecto_t *efecto, int16_t sample)
{
    int16_t salida = 0;
    switch (efecto->efecto)
    {
    case EFECTO_NONE:
        salida = efecto_none_apply(efecto, sample);
        break;
    case EFECTO_MUTE:
        salida = efecto_mute_apply(efecto, sample);
        break;
    case EFECTO_ATENUACION:
        salida = efecto_atenuacion_apply(efecto, sample);
        break;
    case EFECTO_DELAY:
        salida = efecto_delay_apply(efecto, sample);
        break;
    case EFECTO_OVERDRIVE:
        salida = efecto_overdrive_apply(efecto, sample);
        break;
    case EFECTO_DISTORTION:
        salida = efecto_distortion_apply(efecto, sample);
        break;
    case EFECTO_FUZZ:
        salida = efecto_fuzz_apply(efecto, sample);
        break;
    default:
        break;
    }
    return salida;
}


