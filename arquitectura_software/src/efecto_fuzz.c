/** \file efecto_fuzz.c
* A brief file description.
* Created on:    2022/07/11
* Last modified: 2022/07/14 10:47:46
*/

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "fixedpoint.h"
#include "efectos.h"
#include "efectos_int.h"


typedef struct efecto_fuzz_internals_str {
    uint8_t id;
} efecto_fuzz_internals_t;

efecto_t *efecto_fuzz_create() {
    static uint8_t id = 0;
    efecto_fuzz_internals_t *fuzz_internals;
    efecto_fuzzparams_t *fuzz_params;

    efecto_t * efecto_ptr = malloc(sizeof(efecto_t));
    efecto_ptr->efecto = EFECTO_FUZZ;
    
    efecto_ptr->internals = malloc(sizeof(efecto_fuzz_internals_t));
    fuzz_internals=efecto_ptr->internals;
    fuzz_internals->id = id++;

    efecto_ptr->params = malloc(sizeof(efecto_fuzzparams_t));
    fuzz_params=efecto_ptr->params;
    fuzz_params->gain = 32767; 
    fuzz_params->mix = 8192;
    fuzz_params->max_abs_x = 32401; 
    fuzz_params->max_abs_y = 32401;
    fuzz_params->max_abs_z = 7248; 

    return efecto_ptr;
}

void efecto_fuzz_update(efecto_t * efecto, efecto_fuzzparams_t * params) {
    efecto_fuzzparams_t *fuzz_params = efecto->params;
    fuzz_params=efecto->params;
    fuzz_params->gain = params->gain;
    fuzz_params->mix = params->mix;
    fuzz_params->max_abs_x = params->max_abs_x;
    fuzz_params->max_abs_y = params->max_abs_y;
    fuzz_params->max_abs_z = params->max_abs_z;
}

int16_t efecto_fuzz_apply(efecto_t * efecto, int16_t sample) {
    efecto_fuzzparams_t *fuzz_params = efecto->params;
    int16_t gain = fuzz_params->gain;
    int32_t mix = fuzz_params->mix;
    int16_t max_abs_x = fuzz_params->max_abs_x;
    int16_t max_abs_y = fuzz_params->max_abs_y;
    int16_t max_abs_z = fuzz_params->max_abs_z;
    int32_t input_x_gain; 
    int16_t input_x_gain_norm;
    int16_t sign_x_gain_norm;
    uint32_t signal_exp;
    int32_t signal_exp_desp;
    int32_t z;
    int32_t y1;
    int16_t y1_desp;
    int16_t y1_norm;
    int32_t y2;
    int16_t y2_desp;
    int32_t y;
    int16_t y_norm;
    int32_t y_norm_desp;

    input_x_gain=(int32_t)sample*gain; 
    input_x_gain_norm=(int32_t)input_x_gain/max_abs_x;
    sign_x_gain_norm=sign(-input_x_gain_norm)*(int32_t)input_x_gain_norm;
    signal_exp=exponent((uint32_t)sign_x_gain_norm); 
    signal_exp_desp=(int32_t)signal_exp>>1; // Esto creo que es porque está en formato 17.15 la exponencial
    z=sign(-input_x_gain_norm)*((int32_t)16384-signal_exp_desp); 
    y1=(int32_t)mix*z;
    y1_desp=y1>>15;
    y1_norm=(int32_t)y1_desp*max_abs_x/max_abs_z;
    y2=(INT16_MAX-mix)*(int32_t)sample;
    y2_desp=y2>>16;
    y=(int32_t)y1_norm+y2_desp; 
    y_norm=(int32_t)y*max_abs_x/max_abs_y; 
    y_norm_desp=(int32_t)y_norm<<4;

    return y_norm_desp;    
}

