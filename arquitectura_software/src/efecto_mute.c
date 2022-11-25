/** \file efecto_mute.c
* A brief file description.
* Created on:    2022/07/11
* Last modified: 2022/07/13 21:26:35
*/

#include <stdlib.h>
#include "efectos.h"
#include "efectos_int.h"

typedef struct efecto_mute_internals_str
{
    uint8_t id;
} efecto_muteinternals_t;

efecto_t *efecto_mute_create() { 
    static uint8_t id=0;
    efecto_muteinternals_t *muteinternals;
    efecto_t * efecto_ptr = malloc(sizeof(efecto_t));
    efecto_ptr->efecto = EFECTO_MUTE;
    efecto_ptr->internals = malloc(sizeof(efecto_muteinternals_t));
    muteinternals=efecto_ptr->internals;
    muteinternals->id = id++;
    efecto_ptr->params = NULL;
    return efecto_ptr;
}

int16_t efecto_mute_apply(efecto_t * efecto, int16_t sample) {
    return 0;
}
