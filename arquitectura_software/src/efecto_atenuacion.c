/** \file efecto_atenuacion.c
 * A brief file description.
 * Created on:    2022/07/13
 * Last modified: 2022/07/14 10:10:38
 */

#include <stdlib.h>
#include "efectos.h"
#include "efectos_int.h"

typedef struct efecto_atenuacion_internals_str
{
    uint8_t id;
} efecto_atenuacioninternals_t;

efecto_t *efecto_atenuacion_create()
{
    static uint8_t id = 0;
    efecto_atenuacioninternals_t *atenuacioninternals;
    efecto_atenuacionparams_t *atenuacionparams;

    efecto_t *efecto_ptr = malloc(sizeof(efecto_t));
    efecto_ptr->efecto = EFECTO_ATENUACION;

    efecto_ptr->internals = malloc(sizeof(efecto_atenuacioninternals_t));
    atenuacioninternals = efecto_ptr->internals;
    atenuacioninternals->id = id++;

    efecto_ptr->params = malloc(sizeof(efecto_atenuacionparams_t));
    atenuacionparams = efecto_ptr->params;
    atenuacionparams->atenuacion = 4096;

    return efecto_ptr;
}

void efecto_atenuacion_update(efecto_t *efecto, efecto_atenuacionparams_t *params)
{
    efecto_atenuacionparams_t *atenuacionparams = efecto->params;
    atenuacionparams->atenuacion = params->atenuacion;
}

int16_t efecto_atenuacion_apply(efecto_t *efecto, int16_t sample)
{
    efecto_atenuacionparams_t *atenuacionparams = efecto->params;
    int32_t atenuacion = atenuacionparams->atenuacion;
    int32_t sample_x_atenuacion= (int32_t)sample * atenuacion;
    
    return (sample_x_atenuacion>>15);
}
