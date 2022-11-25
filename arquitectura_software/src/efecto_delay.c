/** \file efecto_delay.c
* A brief file description.
* Created on:    2022/07/11
* Last modified: 2022/07/14 10:47:46
*/

#include <stdlib.h>
#include <stdint.h>
#include "efectos.h"
#include "efectos_int.h"


typedef struct efecto_delay_internals_str {
    uint8_t id;
    int16_t fzp1[640];
    uint16_t index;
} efecto_delayinternals_t;

efecto_t *efecto_delay_create() {
    static uint8_t id = 0;
    static int16_t fzp1[640] = {0}; 
    static uint16_t index = 0;
    efecto_delayinternals_t *delayinternals;
    efecto_delayparams_t *delayparams;

    efecto_t * efecto_ptr = malloc(sizeof(efecto_t));
    efecto_ptr->efecto = EFECTO_DELAY;
    
    efecto_ptr->internals = calloc(sizeof(efecto_delayinternals_t)); // inicializo todo a cero y asi no pongo fzp1 y la i a cero
    delayinternals=efecto_ptr->internals;
    delayinternals->id = id++;
    //delayinternals->fzp1 = 0;
    //delayinternals->index = 0;

    efecto_ptr->params = malloc(sizeof(efecto_delayparams_t));
    delayparams=efecto_ptr->params;
    delayparams->gain = 49152;

    return efecto_ptr;
}

void efecto_delay_update(efecto_t * efecto, efecto_delayparams_t * params) {
    efecto_delayparams_t *delayparams = efecto->params;
    delayparams=efecto->params;
    delayparams->gain = params->gain;
}

int16_t efecto_delay_apply(efecto_t * efecto, int16_t sample) {
    /*efecto_delayinternals_t *delayinternals = efecto->internals;
    efecto_delayparams_t *delayparams = efecto->params;
    int16_t fzp1[index] = delayinternals->fzp1; // trabajar directamente con delayinternals->fzp1
    uint16_t index = delayinternals->index;
    int32_t gain = delayparams->gain;
    int32_t input_desp; // <31,30>
    int32_t const_x_delay; // <32,30>
    int32_t output;  // <32,30>

    input_desp=(int32_t)sample<<15; // <31,30>
    const_x_delay=fzp1[index]*(int32_t)gain; // <31,30>
    output = (int32_t)input_desp+const_x_delay; // <32,30>
    //fzp1 = (int32_t)output>>16; // <16,15>
    fzp1[index] = (int32_t)output>>16;
    index++;
    if (index>= 560) {index = 0;}	

    return output>>15;
    */
    return 0;
}

