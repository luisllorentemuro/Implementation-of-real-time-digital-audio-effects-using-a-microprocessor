/** \file efecto_distortion.c
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


typedef struct efecto_distortion_internals_str {
    uint8_t id;
} efecto_distortion_internals_t;

efecto_t *efecto_distortion_create() {
    static uint8_t id = 0;
    efecto_distortion_internals_t *distortion_internals;
    efecto_distortionparams_t *distortion_params;

    efecto_t * efecto_ptr = malloc(sizeof(efecto_t));
    efecto_ptr->efecto = EFECTO_DISTORTION;
    
    efecto_ptr->internals = malloc(sizeof(efecto_distortion_internals_t));
    distortion_internals=efecto_ptr->internals;
    distortion_internals->id = id++;

    efecto_ptr->params = malloc(sizeof(efecto_distortionparams_t));
    distortion_params=efecto_ptr->params;
    distortion_params->gain = 96000; 
    distortion_params->mix = 32767;

    return efecto_ptr;
}

void efecto_distortion_update(efecto_t * efecto, efecto_distortionparams_t * params) {
    efecto_distortionparams_t *distortion_params = efecto->params;
    distortion_params=efecto->params;
    distortion_params->gain = params->gain;
    distortion_params->mix = params->mix;
}

int16_t efecto_distortion_apply(efecto_t * efecto, int16_t sample) {
    efecto_distortionparams_t *distortion_params = efecto->params;
    int16_t gain = distortion_params->gain;
    int32_t mix = distortion_params->mix;
    int32_t input_x_gain; 
    int16_t input_x_gain_desp;
    uint32_t signal_exp;
    int16_t signal_exp_desp;
    int32_t z;
    int32_t y1;
    //int16_t y1_desp;
    int32_t y2;
    //int16_t y2_desp;
    int32_t y;
    //int16_t y_desp;

    input_x_gain=(int32_t)sample*gain; 
    input_x_gain_desp=input_x_gain>>15;
    signal_exp=exponent(-abs((uint32_t)input_x_gain_desp)); 
    signal_exp_desp=signal_exp>>1; // Esto creo que es porque está en formato 17.15 la exponencial
    if(input_x_gain>0){
        z=(int32_t)16384-signal_exp_desp;  
    }else if (input_x_gain<0){
        z=signal_exp_desp-(int32_t)16384; 
    }else{
        z=0;
    }

    y1=(int32_t)mix*z;
    //y1_desp=y1>>15;
    y2=(INT16_MAX-mix)*(int32_t)sample;
    //y2_desp=y2>>16;
    // HASTA AQUÍ ESTÁ BIEN. LO DE ABAJO CREO QUE TAMBIÉN, PERO PIERDO MÁS PRECISIÓN DE LA QUE ME GUSTARÍA
    //y=(int32_t)y1_desp+y2_desp; 
    y=(int32_t)y1+y2>>1; 
    //return y1>>14;
    //return y2>>15;
    return y>>13;    
}

