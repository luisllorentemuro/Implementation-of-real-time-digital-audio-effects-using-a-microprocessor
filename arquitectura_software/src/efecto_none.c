/** \file efecto_none.c
* A brief file description.
* Created on:    2022/07/11
* Last modified: 2022/07/13 21:26:35
*/

#include <stdlib.h>
#include "efectos.h"
#include "efectos_int.h"

typedef struct efecto_none_internals_str
{
    uint8_t id;
} efecto_noneinternals_t;

efecto_t *efecto_none_create() { 
    static uint8_t id=0;
    efecto_noneinternals_t *noneinternals;
    efecto_t * efecto_ptr = malloc(sizeof(efecto_t));
    efecto_ptr->efecto = EFECTO_NONE;
    efecto_ptr->internals = malloc(sizeof(efecto_noneinternals_t));
    noneinternals=efecto_ptr->internals;
    noneinternals->id = id++;
    efecto_ptr->params = NULL;
    return efecto_ptr;
}

int16_t efecto_none_apply(efecto_t * efecto, int16_t sample) {
    return sample;
}
