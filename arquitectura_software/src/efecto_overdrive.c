/** \file efecto_overdrive.c
* A brief file description.
* Created on:    2022/07/11
* Last modified: 2022/07/13 21:26:35
*/

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "efectos.h"
#include "efectos_int.h"

typedef struct efecto_overdrive_internals_str
{
    uint8_t id;
} efecto_overdriveinternals_t;

efecto_t *efecto_overdrive_create() { 
    static uint8_t id=0;
    efecto_overdriveinternals_t *overdriveinternals;
    efecto_t * efecto_ptr = malloc(sizeof(efecto_t));
    efecto_ptr->efecto = EFECTO_OVERDRIVE;
    efecto_ptr->internals = malloc(sizeof(efecto_overdriveinternals_t));
    overdriveinternals=efecto_ptr->internals;
    overdriveinternals->id = id++;
    efecto_ptr->params = NULL;
    return efecto_ptr;
}

int16_t efecto_overdrive_apply(efecto_t * efecto, int16_t sample) {
    int16_t th; 
    int32_t tercio;
    int32_t input_x_4;
    int32_t input_cuadrado;
    int16_t input_cuadrado_desp;
    int32_t input_cuadrado_x_3;
    int16_t input_cuadrado_x_3_desp;
    int32_t y; 
    int32_t output; 

    th=10923; // (1/3*2^15) (threshold for symmetrical soft clipping by Schetzen Formula)
        
    if (abs(sample)<th)
    {
        y=(int32_t)sample<<1; //otra opcion mejor si x es 16,15 y quiero multipliicarlo por 2 es decir tengo 16,14. asi no toco el numero
        output=y>>3;
    }
        
    if (abs(sample)>=th)
    {
        if (sample>0)
        {
            // -1/3 -3x^2 + 4x
            tercio=-2730.67; 
            input_cuadrado = -(int32_t)sample*sample;
            input_cuadrado_desp = input_cuadrado>>15;
            input_cuadrado_x_3=(int32_t)input_cuadrado_desp*3;
            input_cuadrado_x_3_desp=input_cuadrado_x_3>>2;
            y=(int32_t)input_cuadrado_x_3_desp+tercio+sample;
            output=y>>1;
        }
        if (sample<0)
        {
            // 1/3 + 3*(abs(x))^2 - 4*abs(x)
            tercio=2730.67; 
            input_cuadrado = (int32_t)sample*sample;
            input_cuadrado_desp = input_cuadrado>>17;
            input_cuadrado_x_3=(int32_t)input_cuadrado_desp*3;
            input_x_4=(int32_t)-abs(sample);
            y=(int32_t)input_cuadrado_x_3+(int32_t)tercio+(int32_t)input_x_4;
            output=y>>1;
        }
    } 
    
    if (abs(sample)>((int32_t)th<<1)) 
    {
        if (sample>0)
        {
            y=INT16_MAX; 
            output=y>>3;
        }
        if (sample<0)
        {
            y=-INT16_MAX; 
            output=y>>3;
        }  
    }
    
    return output<<3;
}
